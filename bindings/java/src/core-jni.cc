/*****************************************************************************
 * vlc-libvlc-jni.cc: JNI interface for vlc Java Bindings
 *****************************************************************************
 * Copyright (C) 1998-2006 the VideoLAN team
 *
 * Authors: Filippo Carone <filippo@carone.org>
 *          Philippe Morin <phmorin@free.fr>
 *
 * $Id: core-jni.cc 156 2006-08-01 09:23:01Z littlejohn $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 *****************************************************************************/

/* These are a must*/
#include <jni.h>
#include <vlc/libvlc.h>

#include <stdio.h>  // for printf
#include <stdlib.h> // for calloc
#include <string.h> // for strcmp
#include <unistd.h> // for usleep

/* JVLC internal imports, generated by gcjh */
#include "../includes/JVLC.h"

#include <jawt.h>
#include <jawt_md.h>

#include <X11/Xlib.h> // for Xlibs graphics functions

#include "utils.h"


jlong getClassInstance (JNIEnv *env, jobject _this);

JNIEXPORT jlong JNICALL Java_org_videolan_jvlc_JVLC_createInstance (JNIEnv *env, jobject _this, jobjectArray args) {

    long res;
    int argc;
    const char **argv;

    libvlc_exception_t *exception = ( libvlc_exception_t * ) malloc( sizeof( libvlc_exception_t ) );

    libvlc_exception_init( exception );
  
    argc = (int) env->GetArrayLength((jarray) args) + 1;
    argv = (const char **) malloc(argc * sizeof(char*));

    argv[0] = "vlc";
    
    
    for (int i = 0; i < argc - 1; i++) {
        argv[i+1] = env->GetStringUTFChars((jstring) env->GetObjectArrayElement(args, i),
                                         0
        );
    }

    res = (long) libvlc_new(argc, (char**) argv, exception );

    free( exception );
    free( argv );

    return res;

}

JNIEXPORT void JNICALL Java_org_videolan_jvlc_JVLC__1destroy (JNIEnv *env, jobject _this) 
{
    long instance;
    
    instance = getClassInstance( env, _this );

    libvlc_destroy( (libvlc_instance_t *) instance, NULL);

    return;
}


/*
 * Utility functions
 */
jlong getClassInstance (JNIEnv *env, jobject _this) {
    /* get the id field of object */
    jclass    cls   = env->GetObjectClass(_this);
    jmethodID mid   = env->GetMethodID(cls, "getInstance", "()J");
    jlong     field = env->CallLongMethod(_this, mid);
    return field;
}
