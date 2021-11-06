/*
 *  Canon Inkjet Printer Driver for Linux
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
 */

/*** Defines ***/
// Error codes.
#define ID_ERR_NO_ERROR					0	// No error.
#define ID_ERR_ARGUMENT_ERR				-1	// Argument error.
#define ID_ERR_MEM_ALLOC_FAILED			-2	// Memory allocate failed.
#define ID_ERR_LOAD_PIXMAP_FAILED		-3	// Pixmap load failed.
#define ID_ERR_CUPS_API_FAILED			-4	// CUPS API failed.
#define ID_ERR_NO_PRINTER_ADDED			-5	// No printer registered in CUPS.
#define ID_ERR_UNKNOWN_PRINTER			-6	// Unknown printer.
#define ID_ERR_PRINT_JOB_NOT_EXIST		-7	// Print job not exist.
//Ver.3.10 for Network
#define ID_ERR__NO_RESPONSE				-8	// Print no response.
#define ID_ERR__COLLECTING_STATUS		-9	// Collecting printer status.


/*** Enums ***/
// Error level ID.
typedef enum {
	ID_ERR_LEVEL_NO_ERROR,	// No error.
	ID_ERR_LEVEL_CONTINUE,	// Continue processing.
	ID_ERR_LEVEL_FATAL,		// Fatal error.
} ENUM_ErrorLevelID;
