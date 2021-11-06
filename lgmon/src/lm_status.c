/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2010
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA.
 *
 * NOTE:
 *  - As a special exception, this program is permissible to link with the
 *    libraries released as the binary modules.
 *  - If you write modifications of your own for these programs, it is your
 *    choice whether to permit this exception to apply to your modifications.
 *    If you do not wish that, delete this exception.
 */

#include	<signal.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<sys/wait.h>
#include	<fcntl.h>
#include	<sys/ioctl.h>
#include	<linux/lp.h>
#include	<sys/poll.h>
#include	<asm/errno.h>
#include	<stdlib.h>
#include	<string.h>

#include	"lm.h"
#include	"lmsmsock.h"
#include    "cncl.h"
#include    "cncldef.h"
#include    "cnclcmdutils.h"

volatile static int abort_signal = 0;
static sigset_t sigmask;
static int willbe_end = 0;
extern int sem_id;
extern int device_type;
extern int errno;
extern int print_system;
extern struct ptdev_func dev_access;
extern struct ptdev_func *p_dvacs;

extern int write_printer_command();

extern int ivec_poweroff_flag;
extern int command_type;


#ifdef DEBUG
extern FILE *log_path;
#endif


static struct bjst_rback prn_st;

static int status_get_main(void);
static int check_deviceid_sta(void);

/***** Ver.3.20 for IVEC *****/
static short PreparePrint( char *, short );
static short FinishPrint( char *, short );

void lm_stget_sighand(int sig)
{
	/* SIGTERM receive */
	abort_signal = 1;
}

static void wait_readtime()
{
	if(device_type == DEVICE_TYPE_USB || device_type == DEVICE_TYPE_1394)
		sleep(2);
	else
		sleep(5);
	return;
}

//#define BSCC_SSR "SSR=BST,SFA,CHD,CIL,CIR,LVR,DBS,DWS,DOC,DSC,DJS,CTK,HCF;"
//#define BSCC_SSR "SSR=BST,SFA,CHD,CIL,CIR,HRI,DBS,DWS,DOC,DSC,DJS,CTK,HCF;"
//Ver.2.70
//#define BSCC_SSR "SSR=BST,SFA,CHD,CIL,CIR,HRI,DBS,DWS,DOC,DSC,DJS,CTK,HCF,LVR;"
//Ver.3.00
#define BSCC_SSR ""
#define COUNT_LO 3
#define COUNT_HI 4
#define LENGTH_HI 7
#define LENGTH_LO 8
#define BSCC_HEADSIZE 9
#define STR_STA      "STA:"

static int setup_bscc(int dev_path, char *jobIDStr)
//static int setup_bscc(int dev_path)
{
	int i;
	int error = 0;
	int sta = 0;
	int count;
	char *bscc_com; 
	//                  ESC   [    K   C-lo C-hi INIT  ID  L-hi L-lo (total 9byte)
	char bscc_head[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	//char bscc_head[] = {0x1b,0x5b,0x4b,0x00,0x00,0x00,0x1e,0x00,0x00};
	int size = BSCC_HEADSIZE; /* bscc_head size */
	short	err = -1;

	bscc_com = (char *)(malloc(512));
	if(bscc_com == NULL)
		return -1; /* no RAM */

	/* build BSCC command */
	memset(bscc_com, 0, 512);
	memcpy((void *)bscc_com, (void *)bscc_head, size);    /* BSCC header copy */
//	size = strlen(BSCC_SSR);
//	memcpy((void *)(bscc_com+BSCC_HEADSIZE), (void *)BSCC_SSR, size); /* BSCC body copy */
//	size = strlen(BSCC_SSR) + 4;                          /* size = BSCC body + 4(INIT,ID,L-hi,L-lo) */
//	*(bscc_com + COUNT_LO) = (char)(0x0000ff & size);     /* set Low  byte */
//	*(bscc_com + COUNT_HI) = (char)(0x00ff00 & size);     /* set High byte */
//	size = strlen(BSCC_SSR) + 2;                          /* size = BSCC body + 2(L-hi,L-lo) */
//	*(bscc_com + LENGTH_LO) = (char)(0x0000ff & size);    /* set Low  byte */
//	*(bscc_com + LENGTH_HI) = (char)(0x00ff00 & size);    /* set High byte */

//#ifdef DEBUG
//	for(i=0;i<BSCC_HEADSIZE;i++){
//		fprintf(log_path, "bscc_com[%d] : %x\n", i,bscc_com[i]);
//		fflush(log_path);
//	}
//#endif

	size = strlen(BSCC_SSR) + BSCC_HEADSIZE;
	get_printer_sem(sem_id);
	while(1){
		if(abort_signal){
			error = -1;
			break;
		}

		//Two times call because read results change.
		count = status_to_viewer(&prn_st);	/* pre-read */
		/* get status quickly for Ver.3.20 a3 */
		//count = status_to_viewer(&prn_st);	/* pre-read */

		//20090302 check DEVICEID
		sta = check_deviceid_sta();
		/* printer sleep for Ver.3.20 a3 */
		if( (sta & 0x0030) == 0x0020 )
			error = write_printer_command(dev_path, bscc_com, size);
		else
			error = sta & 0x0001;

		count = status_to_viewer(&prn_st);
		//error = check_deviceid_sta();
		////error = write_printer_command(dev_path, bscc_com, size);
		//count = status_to_viewer(&prn_st);	/* pre-read */
		/* printer sleep for Ver.3.20 a3 */

		if(error){
			if(abort_signal)
				break; /* SIGTERM detect */
			sleep(2);
#ifdef DEBUG
			write_log("LM(S) BSCC write failed now retry.\n");
#endif
			continue;
		}

		if(count){
#ifdef DEBUG
			write_log("LM(S) BSCC setup successed\n");
#endif
			/***** Ver.3.20 for IVEC *****/
			err = PreparePrint( jobIDStr, strlen(jobIDStr) + 1 );
#ifdef DEBUG
			fprintf(log_path, "PreparePrintXXXXXX @ err : %d\n",err);
			fflush(log_path);
#endif
			if( err != CNCL_OK ) break;

			/* BSCC setup success */
			kill(getppid(), SIGUSR2); /* data_output_process start */
			break;
		}
		else
			sleep(1);
	}

	release_printer_sem(sem_id);
	free(bscc_com);

	return error;
}

static int init_rback(int sock, int dev_path)
{
	prn_st.rback_handle = STAT_PATH;    /* stderr (CUPS system) */

	prn_st.dev_handle = dev_path;
	prn_st.fault      = 0;
	prn_st.st_buf     = (char *)malloc(MAX_STATBUF);
	if(prn_st.st_buf == NULL)
		return -1; /* no RAM */

	return 0;
}

int status_get_process(int sm_sock_fd)
{

	int dev_path = PRNT_PATH;
	char jobIDStr[] = "12345678";
	short	err = -1;

	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGTERM);

	/* signal handler setup */
	signal_setup(SIGTERM, lm_stget_sighand);
#ifdef DEBUG
	write_log("LM(S) status_get_process start\n");
#endif

	/* status read back struct init */
	if(init_rback(sm_sock_fd, dev_path) != 0){
#ifdef DEBUG
		write_log("LM(S) init_rback() error\n");
#endif
		exit(0);
	}

	if(print_system == PRNSYS_CUPS){
		sleep(2); /* wait lm_main_cups() and data_output_process() setup */
		if(setup_bscc(dev_path, jobIDStr) != 0){
		//if(setup_bscc(dev_path) != 0){
			free(prn_st.st_buf);
#ifdef DEBUG
			write_log("LM(S) status_get_process end\n");
#endif
			exit(0);
		}
	}

	/* printer status read until SIGTERM receive */
	while(1){

		/* SIGTERM receive? */
		if(abort_signal){
#ifdef DEBUG
			write_log("LM(S) SIGTERM receive(status_get_process)\n");
#endif
			break;
		}

		if(willbe_end == 0){
			signal_block(sigmask);
			status_get_main();
			signal_unblock(sigmask);
		}

		wait_readtime();
	}

	/***** Ver.3.20 for IVEC *****/
	err = FinishPrint( jobIDStr, strlen(jobIDStr) + 1 );
	if( err != CNCL_OK ) goto exit_1;

exit_1:
	free(prn_st.st_buf);

#ifdef DEBUG
	write_log("LM(S) status_get_process end\n");
#endif

	exit(0);
}

static int printing = 0;
#define BST_PRINTING 0x80
#define BST_BUSY     0x20
#define BST_OPCALL   0x08
#define STR_BST      "BST:"
static unsigned char get_bst(char *buf)
{
	char *ptr;
	unsigned char val = 0;
	unsigned char work[2];
	unsigned int  wk;

//	ptr = strstr(buf, STR_BST);
	ptr = strstr(buf+2, STR_BST);
	if(ptr == NULL)
		return val;

	ptr += strlen(STR_BST);
	work[0] = *ptr;
	work[1] = 0x00;
	sscanf(work, "%x", &wk); /* conv Hex string to value(Hi) */
	val = (char)(wk<<4);

	ptr++;
	work[0] = *ptr;
	work[1] = 0x00;
	sscanf(work, "%x", &wk); /* conv HEX string to value(Lo) */
	val |= (char)wk;

	return val;
}

static int status_check(int s_count)
{
	struct bjst_rback *ptr = &prn_st;
	unsigned char bst;

	if(ptr->fault == LM_PRN_POWOFF){
		/* power off detect */

		if(printing){
			kill(getppid(), SIGTERM); /* after print start -> force print end */
			willbe_end = 1;
		}
		else{
			signal_unblock(sigmask);
			setup_bscc(PRNT_PATH, NULL);	  /* before print start -> retry BSCC setup */
			//setup_bscc(PRNT_PATH);	  /* before print start -> retry BSCC setup */
			signal_block(sigmask);
		}

		printing = 0;
		return 0;
	}

	if(s_count == 0){
#ifdef DEBUG
		write_log("LM(S) status is NULL.\n");
#endif
		return 0; /* no status data */
	}

	/******* check bscc format **********/
	bst = get_bst(ptr->st_buf);
#ifdef DEBUG
	fprintf(log_path, "@@@@@@@@@@@@@@@bst : %d\n",bst);
	fflush(log_path);
#endif

	if(printing == 0){
		if(bst & BST_PRINTING){
			printing = 1;
#ifdef DEBUG
			write_log("LM(S) printing flag UP\n");
#endif
		}
	}
	else{
		if(!(bst & BST_PRINTING)){
			printing = 0;
#ifdef DEBUG
			write_log("LM(S) printing flag DOWN\n");
#endif
			kill(getppid(), SIGTERM);
			willbe_end = 1;
		}
	}

	return 0;
}

static int status_get_main(void)
{
	int count;

	get_printer_sem(sem_id);
	count = status_to_viewer(&prn_st);
	release_printer_sem(sem_id);

	if(print_system == PRNSYS_CUPS)
		status_check(count);

	return 0;
}


static int check_deviceid_sta(void)
{
	char	devid[1024];
	char	*ivec = NULL;
	int		error = 0;

	memset(devid, '\0', sizeof(devid));

	if (ioctl(PRNT_PATH, _IOC(_IOC_READ, 'P', 1, sizeof(devid)), devid) == 0){
		if ((ivec = strstr(devid+2, STR_STA)) != NULL){
			{
				int val = 0;
				unsigned char work[2];
				unsigned int  wk;

				ivec = ivec + strlen(STR_STA);

				work[0] = *ivec;
				work[1] = 0x00;
				sscanf(work, "%x", &wk); /* conv Hex string to value(Hi) */
				val = (char)(wk<<4);

				ivec++;
				work[0] = *ivec;
				work[1] = 0x00;
				sscanf(work, "%x", &wk); /* conv HEX string to value(Lo) */
				val |= (char)wk;
#ifdef DEBUG
				fprintf(log_path, "STA = %x\n",val);
				fflush(log_path);
#endif
				error = 0;
				/* printer sleep for Ver.3.20 a3 */
				if(val)
					error = val;
				//if(val & 0x01)
				//	error = 1;
			}
     	}
	}

	return error;
}

/*************************************************************/
/*       PreparePrint( char *jobIDStr, short jobIDStrlen )   */
/*                     jobIDStr    : "00000001"              */
/*                     jobIDStrlen :  9(8 + NULL)            */
/*************************************************************/
static short PreparePrint( char *jobIDStr, short jobIDStrlen )
{
	int	w_size;
	int dev_path = PRNT_PATH;
	short	cnclerr = -1;
	char *cmd_wrbuf = NULL;
	short i=0;

	/* write command buffer */
	cmd_wrbuf = (char *)malloc(MAX_STATBUF); /* 4096 */
	if( !cmd_wrbuf )	return(cnclerr);

	signal_block(sigmask);   /* signal block */
	get_printer_sem(sem_id); /* printer lock */

	if( (command_type == NORMAL_COMMAND) || ((command_type == IVEC__COMMAND) && (ivec_poweroff_flag == IVEC_POWEROFF)) ){
		cnclerr = CNCL_OK;
		goto Err01;
	}
	else {

		/* send  "CNCL_COMMAND_START1" */
		memset((void *)cmd_wrbuf, 0, MAX_STATBUF);
		cnclerr = CNCL_MakePrintCommand( CNCL_COMMAND_START1, cmd_wrbuf, MAX_STATBUF, NULL, "1" );
		if( cnclerr != CNCL_OK )	goto Err01;
		w_size = p_dvacs->ptdev_write(dev_path, cmd_wrbuf, strlen(cmd_wrbuf));
		if( w_size < 0 ) {
			cnclerr = -1;
			goto Err01;
		}
#ifdef DEBUG
		write_log("LM(S) CNCL_COMMAND_START1 successed\n");
#endif

		/* wait "CNCL_CHECK_START1:response" */
		cnclerr = -1;
		while( cnclerr != CNCL_OK ){
#ifdef DEBUG
			fprintf(log_path, "CNCL_CHECK_START1:response1 @  i : %d\n",i);
			fflush(log_path);
			i++;
#endif
			usleep(100000);
			memset((void *)cmd_wrbuf, 0, MAX_STATBUF);
			w_size = p_dvacs->ptdev_read(dev_path, cmd_wrbuf, MAX_STATBUF);
			if( w_size < 0 )	goto Err01;
			cnclerr = CNCL_CheckPrintCommand( CNCL_CHECK_START1, cmd_wrbuf, w_size, jobIDStr, jobIDStrlen );
		}
#ifdef DEBUG
		write_log("LM(S) CNCL_COMMAND_START1 RESPONSE successed usleep(100000)\n");
#endif

		/* send "CNCL_COMMAND_START2" write "jobID" */
		memset((void *)cmd_wrbuf, 0, MAX_STATBUF);
		cnclerr = CNCL_MakePrintCommand( CNCL_COMMAND_START2, cmd_wrbuf, MAX_STATBUF, jobIDStr, "1" );
		if( cnclerr != CNCL_OK )	goto Err01;
		w_size = p_dvacs->ptdev_write(dev_path, cmd_wrbuf, strlen(cmd_wrbuf));
		if( w_size < 0 ) {
			cnclerr = -1;
			goto Err01;
		}
#ifdef DEBUG
		write_log("LM(S) CNCL_COMMAND_START2 successed\n");
#endif

		/* wait "CNCL_CHECK_START2:response" */
		cnclerr = -1;
		i = 0;
		while( cnclerr != CNCL_OK ){
#ifdef DEBUG
			fprintf(log_path, "CNCL_CHECK_START2:response @  i : %d\n",i);
			fflush(log_path);
			i++;
#endif
			usleep(100000);
			memset((void *)cmd_wrbuf, 0, MAX_STATBUF);
			w_size = p_dvacs->ptdev_read(dev_path, cmd_wrbuf, MAX_STATBUF);
			if( w_size < 0 )	goto Err01;
			cnclerr = CNCL_CheckPrintCommand( CNCL_CHECK_START2, cmd_wrbuf, w_size, jobIDStr, jobIDStrlen );
		}
#ifdef DEBUG
		write_log("LM(S) CNCL_COMMAND_START2 RESPONSE successed usleep(100000)\n");
#endif
	}

Err01:
#ifdef DEBUG
	fprintf(log_path, "############# cnclerr, w_size : %d,%d\n",cnclerr,w_size);
	fflush(log_path);
#endif
	release_printer_sem(sem_id); /* signal unblock */
	signal_unblock(sigmask);     /* printer unlock */

	if( !cmd_wrbuf )
		free(cmd_wrbuf);
	return(cnclerr);

}

/*************************************************************/
/*       FinishPrint( char *jobIDStr, short jobIDStrlen )    */
/*                     jobIDStr    : "00000001"              */
/*                     jobIDStrlen :  9(8 + NULL)            */
/*************************************************************/
static short FinishPrint( char *jobIDStr, short jobIDStrlen )
{
	int	w_size;
	int dev_path = PRNT_PATH;
	short	cnclerr = -1;
	char *cmd_wrbuf = NULL;
	short	i = 0;

	char *buf2 = NULL;
	char *buf3 = NULL;
	short	bscc_size = 0;
	short	before_w_size = 0;
	short	k = 0;
	short	count = 0;
	int		ret3 = -1;

	/* write command buffer */
	cmd_wrbuf = (char *)malloc(MAX_STATBUF); /* 4096 */
	if( !cmd_wrbuf )	return(cnclerr);

	/* bscc command buffer */
	buf2 = (char *)malloc(MAX_STATBUF); /* 4096 */
	if( !buf2 ){
		free(cmd_wrbuf);
		return(cnclerr);
	}
	memset(buf2, 0, MAX_STATBUF);

	/* status(xml) command buffer */
	buf3 = (char *)malloc(MAX_STATBUF); /* 4096 */
	if( !buf3 ){
		free(buf2);
		free(cmd_wrbuf);
		return(cnclerr);
	}
	memset(buf3, 0, MAX_STATBUF);

	signal_block(sigmask);   /* signal block */
	get_printer_sem(sem_id); /* printer lock */

	if( (command_type == NORMAL_COMMAND) || ((command_type == IVEC__COMMAND) && (ivec_poweroff_flag == IVEC_POWEROFF)) ){
		cnclerr = CNCL_OK;
		goto Err01;
	}
	else {

		/* send "CNCL_COMMAND_END" & write "jobID" */
		memset((void *)cmd_wrbuf, 0, MAX_STATBUF);
		cnclerr = CNCL_MakePrintCommand( CNCL_COMMAND_END, cmd_wrbuf, MAX_STATBUF, jobIDStr, "1" );
		if( cnclerr != CNCL_OK )	goto Err01;
		w_size = p_dvacs->ptdev_write(dev_path, cmd_wrbuf, strlen(cmd_wrbuf));
		if( w_size < 0 ) {
			cnclerr = -1;
			goto Err01;
		}
#ifdef DEBUG
		write_log("LM(S) CNCL_COMMAND_END successed\n");
#endif

		/* wait "CNCL_CHECK_END:OK" */
		cnclerr = -1;
		while( cnclerr != CNCL_OK ){
			usleep(100000);
			memset((void *)cmd_wrbuf, 0, MAX_STATBUF);
			w_size = p_dvacs->ptdev_read(dev_path, cmd_wrbuf, MAX_STATBUF);
			if( w_size < 0 )	goto Err01;
			cnclerr = CNCL_CheckPrintCommand( CNCL_CHECK_END, cmd_wrbuf, w_size, jobIDStr, jobIDStrlen );

			/* get status when cleaning  */
			/***************************************************/
			/* limit read size r_size <=1024 --> loop read xml */
			/* when core2duo... Ver3.20                        */
			/* call CNCL_GetStatusCommand() for check xml data */
			/***************************************************/
			if( cnclerr != CNCL_OK ){
				ret3 = CNCL_GetStatusCommand( cmd_wrbuf, MAX_STATBUF, buf2, w_size, &bscc_size );
			}

			if( ret3 != CNCL_OK  ){
				short 	stserr = -1;

				count++;

				for(k=0 ;k<w_size; k++)
					buf3[k + before_w_size] = cmd_wrbuf[k];

				w_size = before_w_size + w_size;
				before_w_size = w_size;

				if( (count == 5) || (w_size >= MAX_STATBUF) ){
					count = 0;
					before_w_size = 0;
					memcpy(cmd_wrbuf, buf3, MAX_STATBUF);
					memset(buf3, 0, MAX_STATBUF);
					break;
				}

				stserr = CNCL_GetStatusCommand( buf3, MAX_STATBUF, buf2, w_size, &bscc_size );

				if( stserr == CNCL_OK ){
					count = 0;
					before_w_size = 0;
					memcpy(cmd_wrbuf, buf3, MAX_STATBUF);
					memset(buf3, 0, MAX_STATBUF);
				}
			}
			/***************************************************/

			/* Ver.3.20 a2 */
			if( cnclerr != CNCL_OK ){
			//if( (cnclerr != CNCL_OK) && (i == 20) ){
				write_status_info( &prn_st, w_size, cmd_wrbuf );
#ifdef DEBUG
				fprintf(log_path, "CNCL_CheckPrintCommand w_size : %d , %d\n",w_size,i);
				fflush(log_path);
#endif
				i = 0;
			}
			i++;
			/* get status when cleaning  */
		}
#ifdef DEBUG
		write_log("LM(S) CNCL_COMMAND_END RESPONSE successed usleep(100000)\n");
#endif
	}

Err01:
	release_printer_sem(sem_id); /* signal unblock */
	signal_unblock(sigmask);     /* printer unlock */

	if( !buf2 )
		free(buf2);
	if( !buf3 )
		free(buf3);
	if( !cmd_wrbuf )
		free(cmd_wrbuf);

	return(cnclerr);

}
