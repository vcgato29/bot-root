/*
 * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Further, this software is distributed without any warranty that it is
 * free of the rightful claim of any third person regarding infringement
 * or the like.  Any license provided herein, whether implied or
 * otherwise, applies only to this software file.  Patent licenses, if
 * any, provided herein do not apply to combinations of this program with
 * other software, or any other product whatsoever.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write the Free Software Foundation, Inc., 59
 * Temple Place - Suite 330, Boston MA 02111-1307, USA.
 *
 * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 * Mountain View, CA  94043, or:
 *
 * http://www.sgi.com
 *
 * For further information regarding this notice, see:
 *
 * http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */
/* $Id: gethostname01.c,v 1.3 2003/01/24 01:09:39 cgf Exp $ */
/**********************************************************
 * 
 *    OS Test - Silicon Graphics, Inc.
 * 
 *    TEST IDENTIFIER	: gethostname01
 * 
 *    EXECUTED BY	: anyone
 * 
 *    TEST TITLE	: Basic test for gethostname(2)
 * 
 *    PARENT DOCUMENT	: usctpl01
 * 
 *    TEST CASE TOTAL	: 1
 * 
 *    WALL CLOCK TIME	: 1
 * 
 *    CPU TYPES		: ALL
 * 
 *    AUTHOR		: William Roske
 * 
 *    CO-PILOT		: Dave Fenner
 * 
 *    DATE STARTED	: 03/30/92
 * 
 *    INITIAL RELEASE	: UNICOS 7.0
 * 
 *    TEST CASES
 * 
 * 	1.) gethostname(2) returns...(See Description)
 *	
 *    INPUT SPECIFICATIONS
 * 	The standard options for system call tests are accepted.
 *	(See the parse_opts(3) man page).
 * 
 *    DURATION
 * 	Terminates - with frequency and infinite modes.
 * 
 *    SIGNALS
 * 	Uses SIGUSR1 to pause before test if option set.
 * 	(See the parse_opts(3) man page).
 *
 *    RESOURCES
 * 	None
 * 
 *    ENVIRONMENTAL NEEDS
 *      No run-time environmental needs.
 * 
 *    SPECIAL PROCEDURAL REQUIREMENTS
 * 	None
 * 
 *    INTERCASE DEPENDENCIES
 * 	None
 * 
 *    DETAILED DESCRIPTION
 *	This is a Phase I test for the gethostname(2) system call.  It is intended
 *	to provide a limited exposure of the system call, for now.  It
 *	should/will be extended when full functional tests are written for
 *	gethostname(2).
 * 
 * 	Setup:
 * 	  Setup signal handling.
 *	  Pause for SIGUSR1 if option specified.
 * 
 * 	Test:
 *	 Loop if the proper options are given.
 * 	  Execute system call
 *	  Check return code, if system call failed (return=-1)
 *		Log the errno and Issue a FAIL message.
 *	  Otherwise, Issue a PASS message.
 * 
 * 	Cleanup:
 * 	  Print errno log and/or timing stats if options given
 * 
 * 
 *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#**/

#include <errno.h>
#include <string.h>
#include <signal.h>

  

#include "test.h"
#include "usctest.h"

extern void setup();
extern void cleanup();



const char *TCID="gethostname01";/* Test program identifier.    */
int TST_TOTAL=1;		/* Total number of test cases. */
extern int Tst_count;		/* Test Case counter for tst_* routines */

int exp_enos[]={0};		/* must be a 0 terminated list */

int
main(int ac, char **av)
{
    int lc;		/* loop counter */
    const char *msg;		/* message returned from parse_opts */
    
    char hname[100];	/* host name */

    /***************************************************************
     * parse standard options
     ***************************************************************/
    if ( (msg=parse_opts(ac, av, (option_t *) NULL, NULL)) != (char *) NULL )
	tst_brkm(TBROK, cleanup, "OPTION PARSING ERROR - %s", msg);

    /***************************************************************
     * perform global setup for test
     ***************************************************************/
    setup();

    /* set the expected errnos... */
    TEST_EXP_ENOS(exp_enos);

    /***************************************************************
     * check looping state if -c option given
     ***************************************************************/
    for (lc=0; TEST_LOOPING(lc); lc++) {

	/* reset Tst_count in case we are looping. */
	Tst_count=0;

		
	/* 
	 * TEST CASE:
	 *  Get host name
	 */
	;

	/* Call gethostname(2) */
	TEST(gethostname(hname, sizeof(hname) ));
	
	/* check return code */
	if ( TEST_RETURN == -1 ) {
	    TEST_ERROR_LOG(TEST_ERRNO);
	    tst_resm(TFAIL, "gethostname -  Get host name failed, errno=%d : %s",
		     TEST_ERRNO, strerror(TEST_ERRNO));
	    continue;	/* next loop for MTKERNEL */
	}

	/***************************************************************
	 * only perform functional verification if flag set (-f not given)
	 ***************************************************************/
	if ( STD_FUNCTIONAL_TEST ) {
	    /* No Verification test, yet... */
	    tst_resm(TPASS, "gethostname -  Get host name returned %d", TEST_RETURN);
	} 
    }	/* End for TEST_LOOPING */

    /***************************************************************
     * cleanup and exit
     ***************************************************************/
    cleanup();

    return 0;
}	/* End main */

/***************************************************************
 * setup() - performs all ONE TIME setup for this test.
 ***************************************************************/
void 
setup()
{
    /* capture signals */
    tst_sig(NOFORK, DEF_HANDLER, cleanup);

    /* Pause if that option was specified */
    TEST_PAUSE;
}	/* End setup() */


/***************************************************************
 * cleanup() - performs all ONE TIME cleanup for this test at
 *		completion or premature exit.
 ***************************************************************/
void 
cleanup()
{
    /*
     * print timing stats if that option was specified.
     * print errno log if that option was specified.
     */
    TEST_CLEANUP;

    /* exit with return code appropriate for results */
    tst_exit();
}	/* End cleanup() */


