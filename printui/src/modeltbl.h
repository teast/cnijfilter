/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2010
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
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


#ifndef	_MODELTBL
#define	_MODELTBL

#undef	GLOBAL
#ifdef	DEFINE_GLOBALS
#define	GLOBAL
#else
#define	GLOBAL	extern
#endif

typedef enum {
	UI_MEDIASIZE_ILLEGAL,
	UI_MEDIASIZE_RECOMMEND
} MediaSizeType;

typedef struct {
	MediaSizeType type;
	char *base;
	char *applied;
	char *applied_title;
} MediaSizeTable;

typedef struct {
	short model_id;
	short util_flag;
	MediaSizeTable* media_size_table;
	MediaSizeTable* media_size_table_jp;
	short ext_border;
} ModelTable;

/* Ver.3.40 */
typedef struct {
	short model_id;
	MediaSizeTable* media_size_table;
	MediaSizeTable* media_size_table_us;
	MediaSizeTable* media_size_table_jp;
	short ext_border;
} ModelTable2;


/* Ver.3.20 for envelope size guide */
typedef struct {
	short model_id;
	short *size_list;
} GuideDialogTable;


/* Ver.2.80 : Treat the string ID related to "lever position" as "CNCL value" */
/* of CNCL Object"CNUI_OBJECT_LEVER". */
#define CNUI_OBJECT_LEVER			(1000)
#define CNUI_VALUE_LEVER_LABEL		(0)
#define CNUI_VALUE_LEVER_ALERT		(1)


// Utility button flag.
#define	UF_CLEANING			1
#define	UF_DEEP_CLEANING	2
#define	UF_ROLLER_CLEANING	4
#define UF_PLATE_CLEANING	8
#define	UF_NOZZLE_CHECK		0x10
#define	UF_HEAD_ALIGNMENT	0x20
#define UI_PAPER_SOURCE_SETTING 0x40		// 2008/05/09
#define	UF_INK_RESET		0x100
#define	UF_INK_WARNING		0x200
#define	UF_INK_CARTRIDGE	0x400
#define	UF_POWER_OFF		0x1000
#define	UF_AUTO_POWER		0x2000
#define	UF_CUSTOM			0x4000
#define	UF_QUIET			0x8000

#define	UF_F860	(UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_POWER_OFF)

#define	UF_F360	(UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_POWER_OFF | UF_CUSTOM)

#define	UF_S600	(UF_CLEANING | UF_DEEP_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_CUSTOM)

#define	UF_F900	(UF_CLEANING | UF_DEEP_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_CUSTOM | UF_QUIET)

#define	UF_S300	(UF_CLEANING | UF_DEEP_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_INK_RESET | UF_INK_WARNING \
	| UF_POWER_OFF | UF_AUTO_POWER | UF_CUSTOM)

#define	UF_I250	(UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_INK_RESET | UF_INK_WARNING \
	| UF_POWER_OFF | UF_CUSTOM | UF_QUIET)

#define UF_IP3100 (UF_CLEANING | UF_DEEP_CLEANING | UF_PLATE_CLEANING \
	| UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_CUSTOM | UF_QUIET)

#define UF_IP1500 (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_HEAD_ALIGNMENT \
	| UF_INK_RESET | UF_INK_WARNING | UF_POWER_OFF | UF_CUSTOM | UF_QUIET)

#define UF_IP2200 (UF_CLEANING | UF_DEEP_CLEANING | UF_HEAD_ALIGNMENT \
	| UF_NOZZLE_CHECK | UF_INK_CARTRIDGE | UF_PLATE_CLEANING \
	| UF_ROLLER_CLEANING | UF_POWER_OFF | UF_QUIET | UF_CUSTOM)

#define UF_IP4200 (UF_CLEANING | UF_DEEP_CLEANING | UF_HEAD_ALIGNMENT \
	| UF_NOZZLE_CHECK | UF_PLATE_CLEANING | UF_POWER_OFF \
	| UF_AUTO_POWER | UF_QUIET | UF_CUSTOM)

#define UF_IP7500 (UF_CLEANING | UF_DEEP_CLEANING | UF_HEAD_ALIGNMENT \
	| UF_NOZZLE_CHECK | UF_PLATE_CLEANING | UF_POWER_OFF \
	| UF_AUTO_POWER | UF_QUIET | UF_CUSTOM)

#define UF_IP6600D (UF_CLEANING | UF_DEEP_CLEANING | UF_HEAD_ALIGNMENT \
	| UF_NOZZLE_CHECK | UF_PLATE_CLEANING | UF_POWER_OFF \
	| UF_QUIET | UF_CUSTOM)

#define UF_MP500 (UF_CLEANING | UF_DEEP_CLEANING | UF_HEAD_ALIGNMENT \
	| UF_NOZZLE_CHECK | UF_PLATE_CLEANING | UF_POWER_OFF \
	| UF_QUIET | UF_CUSTOM)

// 2006/05/30
#define UF_MP160 (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_POWER_OFF \
	| UF_INK_CARTRIDGE | UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_IP3300 (UF_CLEANING | UF_DEEP_CLEANING | UF_PLATE_CLEANING \
	| UF_NOZZLE_CHECK | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_MP510 (UF_CLEANING | UF_DEEP_CLEANING | UF_PLATE_CLEANING \
	| UF_NOZZLE_CHECK | UF_POWER_OFF \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_IP4300 (UF_CLEANING | UF_DEEP_CLEANING | UF_PLATE_CLEANING \
	| UF_NOZZLE_CHECK | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_MP600 (UF_CLEANING | UF_DEEP_CLEANING | UF_PLATE_CLEANING \
	| UF_NOZZLE_CHECK | UF_POWER_OFF \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_IP90 (UF_CLEANING | UF_DEEP_CLEANING | UF_PLATE_CLEANING \
	| UF_NOZZLE_CHECK | UF_POWER_OFF | UF_AUTO_POWER | UF_INK_RESET | UF_INK_WARNING \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_IP2500 (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_POWER_OFF \
	| UF_INK_CARTRIDGE | UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_TYPE_A (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_TYPE_B (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_POWER_OFF \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_TYPE_C (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_POWER_OFF \
	| UF_INK_CARTRIDGE | UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

#define UF_TYPE_D (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM | UI_PAPER_SOURCE_SETTING)

#define UF_TYPE_E (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_POWER_OFF \
	| UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM | UI_PAPER_SOURCE_SETTING)

#define UF_TYPE_F (UF_CLEANING | UF_DEEP_CLEANING | UF_ROLLER_CLEANING \
	| UF_PLATE_CLEANING | UF_NOZZLE_CHECK | UF_POWER_OFF | UF_AUTO_POWER \
	| UF_INK_CARTRIDGE | UF_QUIET | UF_HEAD_ALIGNMENT | UF_CUSTOM)

// Media Size table.

#ifdef	DEFINE_GLOBALS

GLOBAL MediaSizeTable g_media_size_table_f850[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
					"media_postcard media_glossy_postcard media_pro_photo",
					"media_postcard media_glossy_postcard media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4 size_env_j6", "size_env_j4 size_env_j6"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_glossy_postcard", "size_post", "size_post"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_f860[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_postcard media_pro_photo",
		"media_postcard media_inkjet_postcard \
		 media_glossy_postcard media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4 size_env_j6", "size_env_j4 size_env_j6"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_glossy_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_f360[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard media_glossy_postcard",
		"media_postcard media_inkjet_postcard media_glossy_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_l",
		"media_postcard media_inkjet_postcard media_glossy_postcard",
		"media_postcard media_inkjet_postcard media_glossy_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4 size_env_j6", "size_env_j4 size_env_j6"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_l", "size_post size_post_l"},
	{UI_MEDIASIZE_RECOMMEND, "media_glossy_postcard", "size_post size_post_l", "size_post size_post_l"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post size_post_l", "size_post size_post_l"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_s600[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_postcard media_pro_photo",
		"media_postcard media_inkjet_postcard \
		 media_glossy_postcard media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4_p size_env_j6_p", "size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_glossy_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_f900[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4_p size_env_j6_p", "size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_s300[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_photocard", "media_glossy_photocard", "media_glossy_photocard"},
	{UI_MEDIASIZE_ILLEGAL, "media_glossy_photocard", "size_photocard", "size_photocard"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4_p size_env_j6_p", "size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_i250[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_10_p size_env_dl_p", "size_env_10_p size_env_dl_p"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_pixus560i[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope", "size_env_j4_p size_env_j6_p", "size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip4200[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip4200_jp[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip7500[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_a4_fine_art", "media_fine_art_paper media_other_fine_art_paper"
											 , "media_fine_art_paper media_other_fine_art_paper"},
	{UI_MEDIASIZE_ILLEGAL, "media_fine_art_paper", "size_a4_fine_art", "size_a4_fine_art"},
	{UI_MEDIASIZE_ILLEGAL, "media_other_fine_art_paper", "size_a4_fine_art", "size_a4_fine_art"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip7500_jp[] =
{
	{UI_MEDIASIZE_ILLEGAL, "size_a4_fine_art", "media_fine_art_paper media_other_fine_art_paper"
											 , "media_fine_art_paper media_other_fine_art_paper"},
	{UI_MEDIASIZE_ILLEGAL, "media_fine_art_paper", "size_a4_fine_art", "size_a4_fine_art"},
	{UI_MEDIASIZE_ILLEGAL, "media_other_fine_art_paper", "size_a4_fine_art", "size_a4_fine_art"},

	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};


GLOBAL MediaSizeTable g_media_size_table_ip4300[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p",
		"size_env_10_p size_env_dl_p \
		 size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip4300_jp[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p",
		"size_env_j4_p size_env_j6_p \
		 size_env_10_p size_env_dl_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};


GLOBAL MediaSizeTable g_media_size_table_ip90[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},

	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_10_p size_env_dl_p",
		"size_env_10_p size_env_dl_p \
		 size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip90_jp[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},

	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_10_p size_env_dl_p",
		"size_env_j4_p size_env_j6_p \
		 size_env_10_p size_env_dl_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};


GLOBAL MediaSizeTable g_media_size_table_ip4500[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy media_photo_paper_plus_glossy_ii",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p",
		"size_env_10_p size_env_dl_p \
		 size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip4500_jp[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy media_photo_paper_plus_glossy_ii",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p",
		"size_env_j4_p size_env_j6_p \
		 size_env_10_p size_env_dl_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

/* Ver.2.90 */
GLOBAL MediaSizeTable g_media_size_table_ip100[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy \
		 media_photo_paper_plus_glossy_ii media_photo_paper_plus_semi_gloss",	//add Semi-gloss
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p",
		"size_env_10_p size_env_dl_p \
		 size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip100_jp[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy \
		 media_photo_paper_plus_glossy_ii media_photo_paper_plus_semi_gloss",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p",
		"size_env_j4_p size_env_j6_p \
		 size_env_10_p size_env_dl_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};


/* Ver.3.00 */
GLOBAL MediaSizeTable g_media_size_table_ip4600[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy \
		 media_photo_paper_plus_glossy_ii media_photo_paper_plus_semi_gloss \
		 media_photo_paper_pro_ii",	//add media_photo_paper_pro_ii
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_photo_paper_pro_ii"},//add media_photo_paper_pro_ii and remove media_pro_photo
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p",
		"size_env_10_p size_env_dl_p \
		 size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_ip4600_jp[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy \
		 media_photo_paper_plus_glossy_ii media_photo_paper_plus_semi_gloss \
		 media_photo_paper_pro_ii",	//add media_photo_paper_pro_ii
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_photo_paper_pro_ii"},//add media_photo_paper_pro_ii and remove media_pro_photo
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p",
		"size_env_j4_p size_env_j6_p \
		 size_env_10_p size_env_dl_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};



/* Ver.3.10 */
GLOBAL MediaSizeTable g_media_size_table_mx860[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy \
		 media_photo_paper_plus_glossy_ii media_photo_paper_plus_semi_gloss \
		 media_photo_paper_pro_ii",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_photo_paper_pro_ii"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_dl_p size_env_10_p \
		 size_env_j4_p size_env_j6_p size_user",	//add size_user
		"size_env_10_p size_env_dl_p \
		 size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_mx860_jp[] =
{
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_pro_photo media_photo_plus_glossy \
		 media_photo_paper_plus_glossy_ii media_photo_paper_plus_semi_gloss \
		 media_photo_paper_pro_ii",
		"media_postcard media_inkjet_postcard \
		 media_glossy_photo media_photo_paper_pro_ii"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_j4_p size_env_j6_p \
		 size_env_dl_p size_env_10_p size_user",	//add size_user
		"size_env_j4_p size_env_j6_p \
		 size_env_10_p size_env_dl_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_postcard", "size_post size_post_dbl", "size_post size_post_dbl"},
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard", "size_post", "size_post"},
	{0,NULL,NULL}
};



/* Ver.3.20 */
GLOBAL MediaSizeTable g_media_size_table_09_2h[] =
{
	/* Change Media Type */
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",											/* Ver.3.20 changed */
		"media_address_postcard media_inkjet_postcard media_contents_glossy media_contents_prophoto \
		 media_postcard media_glossy_photo  media_photo_paper_pro_ii \
		 media_photo_paper_plus_semi_gloss media_photo_paper_plus_glossy_ii",
		"media_address_postcard media_inkjet_postcard media_contents_glossy media_contents_prophoto \
		 media_postcard media_glossy_photo media_photo_paper_pro_ii"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	/* Change Page Size */
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_10_p size_env_dl_p size_env_j4_p size_env_j6_p size_user",
		"size_env_10_p size_env_dl_p size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_address_postcard",  "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard",   "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_contents_glossy",   "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_contents_prophoto", "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_postcard",          "size_post size_post_dbl", "size_post size_post_dbl"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_09_2h_jp[] =
{
	/* Change Media Type */
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",											/* Ver.3.20 changed */
		"media_address_postcard media_inkjet_postcard media_contents_glossy media_contents_prophoto \
		 media_postcard media_glossy_photo  media_photo_paper_pro_ii \
		 media_photo_paper_plus_semi_gloss media_photo_paper_plus_glossy_ii",
		"media_address_postcard media_inkjet_postcard media_contents_glossy media_contents_prophoto \
		 media_postcard media_glossy_photo media_photo_paper_pro_ii"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	/* Change Page Size */
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_10_p size_env_dl_p size_env_j4_p size_env_j6_p size_user",
		"size_env_j4_p size_env_j6_p size_env_10_p size_env_dl_p"},					/* differ from other locale */
	{UI_MEDIASIZE_RECOMMEND, "media_address_postcard",  "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard",   "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_contents_glossy",   "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_contents_prophoto", "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_postcard",          "size_post size_post_dbl", "size_post size_post_dbl"},
	{0,NULL,NULL}
};

/* Ver.3.40 */
GLOBAL MediaSizeTable g_media_size_table_10_2h_high[] =
{
	/* Change Media Type (Warning) */
	{UI_MEDIASIZE_ILLEGAL, "size_a4_fine_art", "media_fine_art_paper media_other_fine_art_paper"
											 , "media_fine_art_paper media_other_fine_art_paper"},
	{UI_MEDIASIZE_ILLEGAL, "size_letter_fine_art", "media_fine_art_paper media_other_fine_art_paper"
											 , "media_fine_art_paper media_other_fine_art_paper"},
	/* Change Page Size (Warning) */
	{UI_MEDIASIZE_ILLEGAL, "media_fine_art_paper", "size_a4_fine_art size_letter_fine_art", "size_a4_fine_art size_letter_fine_art"},
	{UI_MEDIASIZE_ILLEGAL, "media_other_fine_art_paper", "size_a4_fine_art size_letter_fine_art", "size_a4_fine_art size_letter_fine_art"},
	/* Change Media Type */
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",											/* Ver.3.20 changed */
		"media_address_postcard media_inkjet_postcard media_contents_glossy media_contents_prophoto \
		 media_postcard media_glossy_photo  media_photo_paper_pro_ii \
		 media_photo_paper_plus_semi_gloss media_photo_paper_plus_glossy_ii",
		"media_address_postcard media_inkjet_postcard media_contents_glossy media_contents_prophoto \
		 media_postcard media_glossy_photo media_photo_paper_pro_ii"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	/* Change Page Size */
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_10_p size_env_dl_p size_env_j4_p size_env_j6_p size_user",
		"size_env_10_p size_env_dl_p size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_address_postcard",  "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard",   "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_contents_glossy",   "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_contents_prophoto", "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_postcard",          "size_post size_post_dbl", "size_post size_post_dbl"},
	{0,NULL,NULL}

};

GLOBAL MediaSizeTable g_media_size_table_10_2h_high_jp[] =
{
	/* Change Media Type (Warning) */
	{UI_MEDIASIZE_ILLEGAL, "size_a4_fine_art", "media_fine_art_paper media_other_fine_art_paper"
											 , "media_fine_art_paper media_other_fine_art_paper"},
	{UI_MEDIASIZE_ILLEGAL, "size_letter_fine_art", "media_fine_art_paper media_other_fine_art_paper"
											 , "media_fine_art_paper media_other_fine_art_paper"},
	/* Change Page Size (Warning) */
	{UI_MEDIASIZE_ILLEGAL, "media_fine_art_paper", "size_a4_fine_art size_letter_fine_art", "size_a4_fine_art size_letter_fine_art"},
	{UI_MEDIASIZE_ILLEGAL, "media_other_fine_art_paper", "size_a4_fine_art size_letter_fine_art", "size_a4_fine_art size_letter_fine_art"},
	/* Change Media Type */
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",											/* Ver.3.20 changed */
		"media_address_postcard media_inkjet_postcard media_contents_glossy media_contents_prophoto \
		 media_postcard media_glossy_photo  media_photo_paper_pro_ii \
		 media_photo_paper_plus_semi_gloss media_photo_paper_plus_glossy_ii",
		"media_address_postcard media_inkjet_postcard media_contents_glossy media_contents_prophoto \
		 media_postcard media_glossy_photo media_photo_paper_pro_ii"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	/* Change Page Size */
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_10_p size_env_dl_p size_env_j4_p size_env_j6_p size_user",
		"size_env_j4_p size_env_j6_p size_env_10_p size_env_dl_p"},					/* differ from other locale */
	{UI_MEDIASIZE_RECOMMEND, "media_address_postcard",  "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard",   "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_contents_glossy",   "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_contents_prophoto", "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_postcard",          "size_post size_post_dbl", "size_post size_post_dbl"},
	{0,NULL,NULL}
};

GLOBAL MediaSizeTable g_media_size_table_10_2h_high_us[] =
{
	/* Change Media Type (Warning) */
	{UI_MEDIASIZE_ILLEGAL, "size_a4_fine_art", "media_fine_art_paper media_other_fine_art_paper"
											 , "media_fine_art_paper media_other_fine_art_paper"},
	{UI_MEDIASIZE_ILLEGAL, "size_letter_fine_art", "media_fine_art_paper media_other_fine_art_paper"
											 , "media_fine_art_paper media_other_fine_art_paper"},
	/* Change Page Size (Warning) */
	{UI_MEDIASIZE_ILLEGAL, "media_fine_art_paper", "size_a4_fine_art size_letter_fine_art", "size_letter_fine_art size_a4_fine_art"},
	{UI_MEDIASIZE_ILLEGAL, "media_other_fine_art_paper", "size_a4_fine_art size_letter_fine_art", "size_letter_fine_art size_a4_fine_art"},
	/* Change Media Type */
	{UI_MEDIASIZE_RECOMMEND, "size_env_10_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_dl_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j4_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_env_j6_p", "media_envelope", "media_envelope"},
	{UI_MEDIASIZE_RECOMMEND, "size_post",											/* Ver.3.20 changed */
		"media_address_postcard media_inkjet_postcard media_contents_glossy media_contents_prophoto \
		 media_postcard media_glossy_photo  media_photo_paper_pro_ii \
		 media_photo_paper_plus_semi_gloss media_photo_paper_plus_glossy_ii",
		"media_address_postcard media_inkjet_postcard media_contents_glossy media_contents_prophoto \
		 media_postcard media_glossy_photo media_photo_paper_pro_ii"},
	{UI_MEDIASIZE_RECOMMEND, "size_post_dbl", "media_postcard", "media_postcard"},
	/* Change Page Size */
	{UI_MEDIASIZE_RECOMMEND, "media_envelope",
		"size_env_10_p size_env_dl_p size_env_j4_p size_env_j6_p size_user",
		"size_env_10_p size_env_dl_p size_env_j4_p size_env_j6_p"},
	{UI_MEDIASIZE_RECOMMEND, "media_address_postcard",  "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_inkjet_postcard",   "size_post", "size_post"},
	{UI_MEDIASIZE_RECOMMEND, "media_contents_glossy",   "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_contents_prophoto", "size_post", "size_post"},	/* Ver.3.20 new */
	{UI_MEDIASIZE_RECOMMEND, "media_postcard",          "size_post size_post_dbl", "size_post size_post_dbl"},
	{0,NULL,NULL}

};



GLOBAL ModelTable g_model_table[] =
{
//	{CND_BJF850,      UF_F860,    g_media_size_table_f850,     	g_media_size_table_f850,			-1},	// old ink.
	{CND_BJF850,      UF_F860,    g_media_size_table_f860,     	g_media_size_table_f860,			-1},	// new ink.
	{CND_F860,        UF_F860,    g_media_size_table_f860,     	g_media_size_table_f860,			-1},
	{CND_F870,        UF_F860,    g_media_size_table_f860,     	g_media_size_table_f860,			-1},
	{CND_BJF360,      UF_F360,    g_media_size_table_f360,     	g_media_size_table_f360,			-1},
	{CND_BJS600,      UF_S600,    g_media_size_table_s600,     	g_media_size_table_s600,			-1},
	{CND_BJS630,      UF_S600,    g_media_size_table_s600,     	g_media_size_table_s600,			-1},
	{CND_BJS6300,     UF_S600,    g_media_size_table_s600,     	g_media_size_table_s600,			-1},
	{CND_BJF900,      UF_F900,    g_media_size_table_f900,     	g_media_size_table_f900,			-1},
	{CND_BJF9000,     UF_F900,    g_media_size_table_f900,     	g_media_size_table_f900,			-1},
	{CND_BJS500,      UF_S600,    g_media_size_table_f900,     	g_media_size_table_f900,			-1},
	{CND_BJS300,      UF_S300,    g_media_size_table_s300,     	g_media_size_table_s300,			-1},
	{CND_PIXUS550I,   UF_F900,    g_media_size_table_f900,     	g_media_size_table_f900,			-1},
	{CND_PIXUS850I,   UF_F900,    g_media_size_table_f900,     	g_media_size_table_f900,			 2},
	{CND_PIXUS950I,   UF_F900,    g_media_size_table_f900,     	g_media_size_table_f900,			 2},
	{CND_I250,        UF_I250,    g_media_size_table_i250,     	g_media_size_table_i250,			-1},
  	{CND_I255,        UF_I250,    g_media_size_table_i250,     	g_media_size_table_i250,			-1},
  	{CND_PIXUS560I,   UF_F900,    g_media_size_table_pixus560i,	g_media_size_table_pixus560i,		 2},
  	{CND_PIXUS860I,   UF_F900,    g_media_size_table_pixus560i,	g_media_size_table_pixus560i,		 2},
  	{CND_PIXUS990I,   UF_F900,    g_media_size_table_pixus560i,	g_media_size_table_pixus560i,		 2},
	{CND_PIXMAIP1000, UF_I250,    g_media_size_table_i250,     	g_media_size_table_i250,			-1}, // Format 4
	{CND_PIXMAIP1500, UF_IP1500,  g_media_size_table_i250,     	g_media_size_table_i250,			-1}, // Format 4
  	{CND_PIXUSIP3100, UF_IP3100,  g_media_size_table_pixus560i,	g_media_size_table_pixus560i,		-1}, // Format 4
 	{CND_PIXUSIP4100, UF_IP3100,  g_media_size_table_pixus560i,	g_media_size_table_pixus560i,		-1}, // Format 4
  	{CND_PIXUSIP8600, UF_IP3100,  g_media_size_table_pixus560i,	g_media_size_table_pixus560i,		-1}, // Format 4
  	{CND_IP2200,      UF_IP2200,  g_media_size_table_ip4200,   	g_media_size_table_ip4200_jp,	-1},
  	{CND_IP4200,      UF_IP4200,  g_media_size_table_ip4200,   	g_media_size_table_ip4200_jp,	-1},
  	{CND_IP6600D,     UF_IP6600D, g_media_size_table_ip4200,   	g_media_size_table_ip4200_jp,	-1}, 
  	{CND_IP7500,      UF_IP7500,  g_media_size_table_ip7500,   	g_media_size_table_ip7500_jp,	-1},	
  	{CND_MP500,       UF_MP500,   g_media_size_table_ip4200,   	g_media_size_table_ip4200_jp,	-1},	
  	{CND_IP3300,      UF_IP3300,  g_media_size_table_ip4300,   	g_media_size_table_ip4300_jp,	-1},	
  	{CND_MP510,       UF_MP510,   g_media_size_table_ip4300,   	g_media_size_table_ip4300_jp,	-1},	
  	{CND_IP4300,      UF_IP4300,  g_media_size_table_ip4300,   	g_media_size_table_ip4300_jp,	-1},	
  	{CND_MP600,       UF_MP600,  g_media_size_table_ip4300,   	g_media_size_table_ip4300_jp,	-1},	
  	{CND_MP160,       UF_MP160,  g_media_size_table_ip4300,   	g_media_size_table_ip4300_jp,	-1},	//2006_0616
  	{CND_IP90,        UF_IP90,   g_media_size_table_ip90,   	g_media_size_table_ip90_jp,	-1},	//2006_1020
  	{CND_IP2500,      UF_IP2500,  g_media_size_table_ip4300,   	g_media_size_table_ip4300_jp,	-1},	//2006_0706 
  	{CND_IP1800,      UF_IP2500,  g_media_size_table_ip4300,   	g_media_size_table_ip4300_jp,	-1},	//2006_0706
  	{CND_MP140,       UF_MP160,   g_media_size_table_ip4500,   	g_media_size_table_ip4500_jp,	-1},
  	{CND_MP210,       UF_MP160,   g_media_size_table_ip4500,   	g_media_size_table_ip4500_jp,	-1},
  	{CND_IP3500,      UF_TYPE_A, g_media_size_table_ip4500,   	g_media_size_table_ip4500_jp,	-1},
  	{CND_IP4500,      UF_TYPE_A, g_media_size_table_ip4500,   	g_media_size_table_ip4500_jp,	-1},
  	{CND_MP610,       UF_TYPE_B, g_media_size_table_ip4500,   	g_media_size_table_ip4500_jp,	-1},
  	{CND_MP520,       UF_TYPE_B, g_media_size_table_ip4500,   	g_media_size_table_ip4500_jp,	-1},
  	{CND_IP100,       UF_TYPE_A, g_media_size_table_ip100,   	g_media_size_table_ip100_jp,	-1},
  	{CND_IP2600,      UF_TYPE_C, g_media_size_table_ip100,   	g_media_size_table_ip100_jp,	-1},
  	{CND_IP3600,      UF_TYPE_D, g_media_size_table_ip4600,   	g_media_size_table_ip4600_jp,	-1},
  	{CND_IP4600,      UF_TYPE_D, g_media_size_table_ip4600,   	g_media_size_table_ip4600_jp,	-1},
  	{CND_MP630,       UF_TYPE_E, g_media_size_table_ip4600,   	g_media_size_table_ip4600_jp,	-1},
  	{CND_MP540,       UF_TYPE_E, g_media_size_table_ip4600,   	g_media_size_table_ip4600_jp,	-1},
  	{CND_MP240,       UF_TYPE_C, g_media_size_table_ip4600,   	g_media_size_table_ip4600_jp,	-1},
  	{CND_MP190,       UF_TYPE_C, g_media_size_table_ip4600,   	g_media_size_table_ip4600_jp,	-1},
  	{CND_IP1900,      UF_TYPE_C, g_media_size_table_ip4600,   	g_media_size_table_ip4600_jp,	-1},
  	{CND_MX860,      UF_TYPE_E, g_media_size_table_mx860,   	g_media_size_table_mx860_jp,	-1},
  	{CND_MX320,      UF_TYPE_C, g_media_size_table_mx860,   	g_media_size_table_mx860_jp,	-1},
  	{CND_MX330,      UF_TYPE_C, g_media_size_table_mx860,   	g_media_size_table_mx860_jp,	-1},
  	{CND_MP250,      UF_TYPE_C, g_media_size_table_09_2h,   	g_media_size_table_09_2h_jp,	-1},
  	{CND_MP270,      UF_TYPE_C, g_media_size_table_09_2h,   	g_media_size_table_09_2h_jp,	-1},
  	{CND_MP490,      UF_TYPE_C, g_media_size_table_09_2h,   	g_media_size_table_09_2h_jp,	-1},
  	{CND_MP550,      UF_TYPE_E, g_media_size_table_09_2h,   	g_media_size_table_09_2h_jp,	-1},
  	{CND_MP560,      UF_TYPE_E, g_media_size_table_09_2h,   	g_media_size_table_09_2h_jp,	-1},
  	{CND_IP4700,     UF_TYPE_D, g_media_size_table_09_2h,   	g_media_size_table_09_2h_jp,	-1},
  	{CND_MP640,      UF_TYPE_E, g_media_size_table_09_2h,   	g_media_size_table_09_2h_jp,	-1},
	{CND_IP2700,     UF_TYPE_F, g_media_size_table_09_2h,   	g_media_size_table_09_2h_jp, -1 },
	{CND_MX340,      UF_TYPE_C, g_media_size_table_09_2h,   	g_media_size_table_09_2h_jp, -1 },
	{CND_MX350,      UF_TYPE_C, g_media_size_table_09_2h,   	g_media_size_table_09_2h_jp, -1 },
	{0,0,NULL}
};

GLOBAL ModelTable2 g_model_table2[] =
{
	{CND_MP495,  g_media_size_table_09_2h, g_media_size_table_09_2h, g_media_size_table_09_2h_jp, -1 },	/* Ver.3.40 */
	{CND_MP280,  g_media_size_table_09_2h, g_media_size_table_09_2h, g_media_size_table_09_2h_jp, -1 },	/* Ver.3.40 */
	{CND_MG5100, g_media_size_table_09_2h, g_media_size_table_09_2h, g_media_size_table_09_2h_jp, -1 },	/* Ver.3.40 */
	{CND_MG5200, g_media_size_table_09_2h, g_media_size_table_09_2h, g_media_size_table_09_2h_jp, -1 },	/* Ver.3.40 */
	{CND_IP4800, g_media_size_table_09_2h, g_media_size_table_09_2h, g_media_size_table_09_2h_jp, -1 },	/* Ver.3.40 */
	{CND_MG6100, g_media_size_table_10_2h_high, g_media_size_table_10_2h_high_us, g_media_size_table_10_2h_high_jp, -1 },	/* Ver.3.40 */
	{CND_MG8100, g_media_size_table_10_2h_high, g_media_size_table_10_2h_high_us, g_media_size_table_10_2h_high_jp, -1 },	/* Ver.3.40 */
	{0,0,NULL}
};

/* Ver.3.20 */
GLOBAL short	size_list_2009_2h[] = {CND_SIZE_ENV_10_P, CND_SIZE_ENV_DL_P, CND_SIZE_ENV_J4_P, CND_SIZE_ENV_J6_P, -1};

/* Envelope Guide */
GLOBAL GuideDialogTable g_env_guide_table[] =
{
	{CND_MP250, size_list_2009_2h },
	{CND_MP270, size_list_2009_2h },
	{CND_MP490, size_list_2009_2h },
	{-1,NULL}
};

#else

GLOBAL ModelTable g_model_table[];
GLOBAL ModelTable2 g_model_table2[];
GLOBAL GuideDialogTable g_env_guide_table[];		/* Ver.3.20 */

#endif



short GetUtilFlag(short model_id);
MediaSizeTable* GetMediaSizeTable(short model_id);
short GetDefaultExtBorderTable(short model_id);

#endif

