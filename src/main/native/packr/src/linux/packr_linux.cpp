/*******************************************************************************
 * Copyright 2015 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#include "../packr.h"

#include <dlfcn.h>
#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

const char __CLASS_PATH_DELIM = ':';

int main(int argc, char** argv) {

    if (!setCmdLineArguments(argc, argv)) {
        return EXIT_FAILURE;
    }

    launchJavaVM(defaultLaunchVMDelegate);

    return 0;
}

bool loadJNIFunctions(GetDefaultJavaVMInitArgs* getDefaultJavaVMInitArgs, CreateJavaVM* createJavaVM) {

    void* handle = dlopen("jre/lib/server/libjvm.so", RTLD_LAZY);
    if (handle == NULL) {
        cerr << dlerror() << endl;
        return false;
    }

	*getDefaultJavaVMInitArgs = (GetDefaultJavaVMInitArgs) dlsym(handle, "JNI_GetDefaultJavaVMInitArgs");
	*createJavaVM = (CreateJavaVM) dlsym(handle, "JNI_CreateJavaVM");

    if ((*getDefaultJavaVMInitArgs == nullptr) || (*createJavaVM == nullptr)) {
        cerr << dlerror() << endl;
        return false;
    }

	return true;
}

const char* getExecutablePath(const char* argv0) {

    static char buf[PATH_MAX];
    uint32_t size = sizeof(buf);

	if (readlink("/proc/self/exe", buf, size) == -1) {
        return argv0;
	}

    return buf;
}

bool changeWorkingDir(const char* directory) {
	return chdir(directory) == 0;
}
