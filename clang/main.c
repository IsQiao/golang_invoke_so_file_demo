#include <dlfcn.h>
#include <stdio.h>
// #include <test.h>

int main()
{
    void (*foo)(void);
    char *error;

    {
        void *handle1 = dlopen("liba.so", RTLD_LAZY);
        if (handle1 == NULL)
        {
            printf("Failed to open a.so\n");
            return 1;
        }

        // 获取函数指针
        foo = dlsym(handle1, "foo");
        if ((error = dlerror()) != NULL)
        {
            fprintf(stderr, "%s\n", error);
            dlclose(handle1);
            return 1;
        }
        foo();
        // 关闭动态链接库
        dlclose(handle1);
    }

    {
        void *handle1 = dlopen("libb.so", RTLD_LAZY);
        if (handle1 == NULL)
        {
            printf("Failed to open b.so\n");
            return 1;
        }

        // 获取函数指针
        foo = dlsym(handle1, "foo");
        if ((error = dlerror()) != NULL)
        {
            fprintf(stderr, "%s\n", error);
            dlclose(handle1);
            return 1;
        }
        foo();
        // 关闭动态链接库
        dlclose(handle1);
    }

    {
        void *handle1 = dlopen("liba.so", RTLD_LAZY);
        if (handle1 == NULL)
        {
            printf("Failed to open a.so\n");
            return 1;
        }

        // 获取函数指针
        foo = dlsym(handle1, "foo");
        if ((error = dlerror()) != NULL)
        {
            fprintf(stderr, "%s\n", error);
            dlclose(handle1);
            return 1;
        }
        foo();
        // 关闭动态链接库
        dlclose(handle1);
    }

    return 0;
}