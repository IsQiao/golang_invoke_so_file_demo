#include <dlfcn.h>
#include <stdio.h>
// #include <nvml.h>

typedef struct nvmlDevice_st *nvmlDevice_t;
#define NVML_DEVICE_NAME_BUFFER_SIZE 64

int main()
{
    char *error;

    void *handle1 = dlopen("libnvidia-ml.so.1", RTLD_LAZY);
    if (handle1 == NULL)
    {
        printf("Failed to open libnvidia-ml.so.1\n");
        return 1;
    }

    {
        int (*nvmlInitWithFlags)(int);
        nvmlInitWithFlags = dlsym(handle1, "nvmlInitWithFlags");
        if ((error = dlerror()) != NULL)
        {
            fprintf(stderr, "%s\n", error);
            dlclose(handle1);
            return 1;
        }
        int ret = nvmlInitWithFlags(RTLD_LAZY);
        printf("ret(nvmlInitWithFlags): %d\n", ret);
    }

    unsigned int deviceCount;
    {
        int (*nvmlDeviceGetCount)(unsigned int *);
        nvmlDeviceGetCount = dlsym(handle1, "nvmlDeviceGetCount");
        if ((error = dlerror()) != NULL)
        {
            fprintf(stderr, "%s\n", error);
            dlclose(handle1);
            return 1;
        }

        int ret = nvmlDeviceGetCount(&deviceCount);
        printf("ret(nvmlDeviceGetCount): %d, devCount: %d\n", ret, deviceCount);
    }

    {
        int (*nvmlDeviceGetHandleByIndex)(unsigned int index, nvmlDevice_t *device);
        nvmlDeviceGetHandleByIndex = dlsym(handle1, "nvmlDeviceGetHandleByIndex");

        unsigned int i;
        nvmlDevice_t device;
        for (i = 0; i < deviceCount; i++)
        {
            int ret = nvmlDeviceGetHandleByIndex(i, &device);
            printf("ret(nvmlDeviceGetHandleByIndex): %d, idx: %d, dev pointer: %p\n", ret, i, &device);

            {
                char name[NVML_DEVICE_NAME_BUFFER_SIZE];

                int (*nvmlDeviceGetName)(nvmlDevice_t device, char *name, unsigned int length);
                nvmlDeviceGetName = dlsym(handle1, "nvmlDeviceGetName");

                int ret = nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_BUFFER_SIZE);
                printf("ret(nvmlDeviceGetName): %d, name: %s\n", ret, name);
            }
        }
    }

    dlclose(handle1);

    return 0;
}
