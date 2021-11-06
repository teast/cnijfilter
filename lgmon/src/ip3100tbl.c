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


/*
 * pixusip3100tbl.c 
 *
 * The conversion table for s300, and a model dependence function table.
 */


/*
 * include necessary headers ...
 */
#include "bscc2sts.h"
#include "commonfunc.h"

/* for pixusip3100 conversion table*/

/*
 * The present busy detailed status.
 */
ST_BSCC2STS pixusip3100_dbs2busy[]={
  {"NO"," "},
  {"UK","?"},
  {"WU","S"},
  {"SL","E"},
  {"CL","L"},
  {"CC","F"},
  {"TP","T"},
  {"DS","I"},
  {ENDTAG,ENDTAG}
};

/*
 * The present detailed status of operation.
 */
ST_BSCC2STS pixusip3100_djs2job[]={
  {"NO"," "},
  {"UK","?"},
  {"ID","I"},
  {"PR","P"},
  {"LD","L"},
  {"EJ","F"},
  {"CC","C"},
  {ENDTAG,ENDTAG}
};

/*
 * The kind of cartridge with which the present printer is equipped.
 */
ST_BSCC2STS pixusip3100_chd2type[]={
  {"NO"," "},
  {"CL","E"},
  {ENDTAG,ENDTAG}
};

ST_BSCC2STS pixusip3100_prname2exchange[]={
  {"PIXUSIP3100","F"},
  {ENDTAG,ENDTAG}
};


/*
 * Residual quantity detection of ink.
 */
ST_BSCC2STS pixusip3100_cil2inkchk[]={
  {"ON","Y"},
  {ENDTAG,ENDTAG}
};

/*
 * Position information between papers.
 */

ST_BSCC2STS pixusip3100_lvr2posit[]={
  {"GAL,W"," "},
  {"GAL,N"," "},
  {ENDTAG,ENDTAG}
};


/*
 * Details of the present warning state.
 */
ST_BSCC2STS pixusip3100_dws2warn[]={
  {"NO"," "},
  {"UK","?"},
  {"1513","C"},
  {"1512","M"},
  {"1511","Y"},
  {"1501","L"},
  {"1852","g"},
  {"1900","1900"},
  {"1910","1910"},
  {ENDTAG,ENDTAG}
};


/*
 * Details of the present operator call state.
 */
ST_BSCC2STS pixusip3100_doc2operate[]={
  {"NO"," "},
  {"UK","?"},
  {"1200","v"},
  {"1250","o"},		// v2.5
  {"1000","V"},
  {"1003","p"},		// v2.5
  {"1300","q"},
  {"1303","j"},		// v2.5
  {"1304","Q"},		// v2.5
  {"1401","H"},
  {"1613","C"},
  {"1612","M"},
  {"1611","Y"},
  {"1601","L"},
  {"1403","R"},
  {"1405","R"},
  {"1700","I"},
  {"1841","G"},	// v2.5
  {"1851","G"},	//
  {"1846","F"},	// v2.5
  {"1856","F"},	// v2.5
  {"2001","U"},	// 
  {"2500","A"},	// v2.5
  {ENDTAG,ENDTAG}
};


/*
 * Information on a service call.
 */
ST_BSCC2STS pixusip3100_dsc2service[]={
  {"NO"," "},
  {"UK","?"},
  {"5100","5100"},
  {"5200","5200"},
  {"5400","5400"},
  {"5B00","I"},
  {"5C00","5C00"},
  {"6800","6800"},
  {ENDTAG,ENDTAG}
};


/*
 * The function table for pixusip3100.
 */
static const FUNCOFMODELSETPROCESS
 pixusip3100setstsfunctable[] = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  pixusip3100_setoperate,
  NULL,
  pixusip3100_setink,
  NULL,
  NULL,
};


/*
 * Arrangement of the conversion table corresponding to the function.
 */
ST_BSCC2STS *p_ip3100chgtbl[] = {
  NULL,
  pixusip3100_dbs2busy,
  pixusip3100_djs2job,
  pixusip3100_cil2inkchk,
  pixusip3100_chd2type,
  pixusip3100_prname2exchange,
  pixusip3100_lvr2posit,
  pixusip3100_dws2warn,
  pixusip3100_doc2operate,
  pixusip3100_dsc2service,
  NULL,
  NULL,
  NULL,
};


/*
 * The corresponding function is called one by one.
 */
int processforip3100(ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf)
{
  int i;
  int ret=0;

  for(i=0; i<MAXFUNCNUM; i++ ){
    if( pixusip3100setstsfunctable[i] == NULL){
      ret = selectcommonfunc(p_s+i, p_ip3100chgtbl[i], p_tbl, i);
      if(ret != OK){
		break;
      }
    } else {
      ret = (*pixusip3100setstsfunctable[i])(p_s+i, p_ip3100chgtbl[i], p_tbl, p_bsccbuf);
      if(ret != OK){
		break;
      }
    }
  }
  return(ret);
}
