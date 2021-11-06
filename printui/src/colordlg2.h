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


#include "dialog.h"

typedef struct
{
	UIDialog dialog;

	short cyan_balance;
	short magenta_balance;
	short yellow_balance;
	short density_balance;
	short contrast_balance;

	short tone_balance; /* Ver.3.40 */

	short vivid;
	short color_correct;
	short gamma;
	short default_gamma;
	short default_intent;
	short intent_num;	/* Ver.2.80 */
} UIColorDialog2;


UIColorDialog2* CreateColorDialog2(UIDialog* parent);
void ShowColorDialog2(UIColorDialog2* dialog);
void HideColorDialog2(UIColorDialog2* dialog, gboolean apply);
UIColorDialog2* ReCreateColorDialog2(UIColorDialog2* dialog, UIDialog* parent);

