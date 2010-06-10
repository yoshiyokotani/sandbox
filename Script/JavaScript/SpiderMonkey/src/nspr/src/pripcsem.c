/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Netscape Portable Runtime (NSPR).
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1999-2000
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

/*
 * File: pripcsem.c
 *
 * Description: implements the named semaphores API in prsemipc.h
 * for classic NSPR.  
 */

#include "private/primpl.h"


PR_IMPLEMENT(PRStatus) PR_NewSemaphore(PRSem *sem, PRUintn value)
{
    sem = CreateSemaphore(NULL, value, 0x7fffffff, NULL);
	if(sem != NULL)
		return PR_SUCCESS;

	return PR_FAILURE;
}

PR_IMPLEMENT(PRSem *) PR_OpenSemaphore(
    const char *name, PRIntn flags, PRIntn mode, PRUintn value)
{
    return _PR_OPEN_SEM(NULL, flags, mode, value);
}

PR_IMPLEMENT(PRStatus) PR_WaitSemaphore(PRSem *sem)
{
    return _PR_TIMED_WAIT_SEM(sem, PR_INTERVAL_NO_TIMEOUT);
}

PR_IMPLEMENT(PRStatus) PR_PostSemaphore(PRSem *sem)
{
    return _PR_POST_SEM(sem);
}


PR_IMPLEMENT(PRStatus) PR_PostMultiSemaphore(PRSem *sem, PRInt32 iPost)
{
    return _PR_POST_MULTI_SEM(sem, iPost);
}

PR_IMPLEMENT(void) PR_CloseSemaphore(PRSem *sem)
{
	CloseHandle(sem);
}

