#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "cuda_profiler_api.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>
const int size = 10 * 1024 * 1024;
const int N = 1024 * 1024;
const int FULL_DATA_SIZE = 2 * N;
const int GPUTHREADNUM = 256;
const int GPUBLOCKNUM = 256;

//����cudamalloc����ѭ��100�ε�����ʱ��
float cuda_malloc_test(int size, bool up)
{
	cudaEvent_t start, stop;
	int *a, *dev_a;
	float elapsedTime;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	a = (int *)malloc(10 * 1024 * 1024 * sizeof(int));
	printf("%p", a);
	if (a == NULL)
	{
		printf("host memory malloc fail!\n");
	}

	cudaError_t cudaStatus = cudaMalloc((void **)&dev_a, size * sizeof(*dev_a));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc failed!\n");
	}

	cudaEventRecord(start, 0);
	for (int i = 0; i < 100; i++)
	{
		if (up)
		{
			cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(*dev_a), cudaMemcpyHostToDevice);
			if (cudaStatus != cudaSuccess)
			{
				fprintf(stderr, "cudaMemcpy Host to Device failed!\n");
				return -1;
			}
		}
		else
		{
			cudaStatus = cudaMemcpy(a, dev_a, size * sizeof(*dev_a), cudaMemcpyDeviceToHost);
			if (cudaStatus != cudaSuccess)
			{
				fprintf(stderr, "cudaMemcpy Device to Host failed!\n");
				return -1;
			}
		}
	}
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);

	free(a);
	cudaFree(dev_a);
	cudaEventDestroy(start);
	cudaEventDestroy(stop);

	return elapsedTime;

}

//����cudaHostAlloc����ѭ��100�ε�����ʱ��
float cuda_host_alloc_test(int size, bool up)
{
	cudaEvent_t start, stop;
	int *a, *dev_a;
	float elapsedTime;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaError_t cudaStatus = cudaHostAlloc((void **)&a, size * sizeof(*a), cudaHostAllocDefault);
	if (cudaStatus != cudaSuccess)
	{
		printf("host alloc fail!\n");
		return -1;
	}

	cudaStatus = cudaMalloc((void **)&dev_a, size * sizeof(*dev_a));
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc failed!\n");
		return -1;
	}

	cudaEventRecord(start, 0);
	for (int i = 0; i < 100; i++)
	{
		if (up)
		{
			cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(*dev_a), cudaMemcpyHostToDevice);
			if (cudaStatus != cudaSuccess)
			{
				fprintf(stderr, "cudaMemcpy Host to Device failed!\n");
				return -1;
			}
		}
		else
		{
			cudaStatus = cudaMemcpy(a, dev_a, size * sizeof(*dev_a), cudaMemcpyDeviceToHost);
			if (cudaStatus != cudaSuccess)
			{
				fprintf(stderr, "cudaMemcpy Device to Host failed!\n");
				return -1;
			}
		}
	}
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);

	cudaFreeHost(a);
	cudaFree(dev_a);
	cudaEventDestroy(start);
	cudaEventDestroy(stop);

	return elapsedTime;

}

//�˺���������һ�����д�ļӷ�
__global__ void kernel(int *a, int *b, int *c)
{
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	if (idx < N)
	{
		for (int i = 0; i < 2000; i++)
		{
			int idx1 = (idx + 1) % GPUTHREADNUM;
			int idx2 = (idx + 2) % GPUTHREADNUM;
			float as = (a[idx] + a[idx1] + a[idx2]) / 3.0f;
			float bs = (b[idx] + b[idx1] + b[idx2]) / 3.0f;
			c[idx] = (as + bs) / 2;
		}
		
	}
}

//�˺���������һ�����д�ļӷ�
__global__ void kernel1(int *a, int *b, int *c)
{
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	if (idx < N)
	{
		a[idx] = 33;
		b[idx] = 33;
		c[idx] = 33;
	}
}
//�˺���������һ�����д�ļӷ�
__global__ void kernel2(int *a, int *b, int *c)
{
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	if (idx < 10)
	{
		c[idx] = 10;
	}
}

void mytest()
{
	//����cudaHostAlloc���������̶��ڴ�
	int *host_a;
	int *dev_a;
	cudaError_t cudaStatus;
	cudaStatus = cudaHostAlloc((void **)&host_a, 10 * sizeof(int), cudaHostAllocMapped| cudaHostAllocWriteCombined);
	cudaHostGetDevicePointer((void**)&dev_a, (void*)host_a, cudaHostAllocDefault);
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaHostAlloc host_a failed!\n");
	}
	//������������
	for (int i = 0; i < 10; i++)
	{
		host_a[i] = i;
		printf("Time taken : %d ms\n", host_a[i]);
	}

	
	kernel2 << <N / GPUBLOCKNUM, GPUTHREADNUM >> >(dev_a, dev_a, dev_a);
	cudaStatus = cudaDeviceSynchronize();
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaDeviceSynchronize failed!\n");
	}
	printf("Time taken : %d ms\n", host_a[0]);
	printf("Time taken : %d ms\n", host_a[1]);
	printf("Time taken : %d ms\n", host_a[2]);
	printf("Time taken : %d ms\n", host_a[3]);
	printf("Time taken : %d ms\n", host_a[4]);
	int a[10] = { 0 };
	cudaMemcpy(a, host_a, 10 * sizeof(int), cudaMemcpyHostToHost);
	cudaMemcpy(a, dev_a, 10 * sizeof(int), cudaMemcpyDeviceToHost);
	//memcpy(a, host_a,10* sizeof(int));
	printf("Time taken : %d ms\n", a[0]);
	printf("Time taken : %d ms\n", a[1]);
	printf("Time taken : %d ms\n", a[2]);
	printf("Time taken : %d ms\n", a[3]);
	printf("Time taken : %d ms\n", a[4]);
	int b[10] = { 100 };
	cudaMemcpy(host_a, b, 10 * sizeof(int), cudaMemcpyHostToHost);
	printf("Time taken : %d ms\n", host_a[0]);
	printf("Time taken : %d ms\n", host_a[1]);
	printf("Time taken : %d ms\n", host_a[2]);
	printf("Time taken : %d ms\n", host_a[3]);
	printf("Time taken : %d ms\n", host_a[4]);
	cudaMemcpy(a, dev_a, 10 * sizeof(int), cudaMemcpyDeviceToHost);

	return;
}
void singlestream()
{
	cudaDeviceProp prop;
	int whichDevice;
	cudaGetDevice(&whichDevice);
	cudaGetDeviceProperties(&prop, whichDevice);
	if (!prop.deviceOverlap)
	{
		printf("Device will not handle overlaps, so no speed up from streams.\n");
		return ;
	}

	cudaEvent_t start, stop;
	float elapsedTime;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

	cudaStream_t stream;
	cudaStreamCreate(&stream);
	int *host_a, *host_b, *host_c;
	int *dev_a, *dev_b, *dev_c;

	cudaError_t cudaStatus;
	cudaStatus = cudaMalloc((void **)&dev_a, N * sizeof(int));
	if (cudaStatus != cudaSuccess)
	{
	printf("cudaMalloc dev_a failed!\n");
	}
	cudaStatus = cudaMalloc((void **)&dev_b, N * sizeof(int));
	if (cudaStatus != cudaSuccess)
	{
	printf("cudaMalloc dev_b failed!\n");
	}
	cudaStatus = cudaMalloc((void **)&dev_c, N * sizeof(int));
	if (cudaStatus != cudaSuccess)
	{
	printf("cudaMalloc dev_c failed!\n");
	}
	cudaStatus = cudaHostAlloc((void **)&host_a, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	if (cudaStatus != cudaSuccess)
	{
	printf("cudaHostAlloc host_a failed!\n");
	}
	cudaStatus = cudaHostAlloc((void **)&host_b, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	if (cudaStatus != cudaSuccess)
	{
	printf("cudaHostAlloc host_b failed!\n");
	}
	cudaStatus = cudaHostAlloc((void **)&host_c, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	if (cudaStatus != cudaSuccess)
	{
	printf("cudaHostAlloc host_c failed!\n");
	}
	for (int i = 0; i < FULL_DATA_SIZE; i++)
	{
	host_a[i] = i - N;
	host_b[i] = i;
	}
	for (int i = 0; i < FULL_DATA_SIZE; i += N)
	{
		cudaStatus = cudaMemcpyAsync(dev_a, host_a + i, N * sizeof(int), cudaMemcpyHostToDevice, stream);
		if (cudaStatus != cudaSuccess)
		{
			printf("cudaMemcpyAsync a failed!\n");
		}
		cudaStatus = cudaMemcpyAsync(dev_b, host_b + i, N * sizeof(int), cudaMemcpyHostToDevice, stream);
		if (cudaStatus != cudaSuccess)
		{
			printf("cudaMemcpyAsync b failed!\n");
		}
		kernel << <N / GPUBLOCKNUM, GPUTHREADNUM, 0, stream >> >(dev_a, dev_b, dev_c);
		cudaStatus = cudaMemcpyAsync(host_c + i, dev_c, N * sizeof(int), cudaMemcpyDeviceToHost, stream);
		if (cudaStatus != cudaSuccess)
		{
			printf("cudaMemcpyAsync c failed!\n");
		}
	}
	cudaStatus = cudaStreamSynchronize(stream);
	if (cudaStatus != cudaSuccess)
	{
	printf("cudaStreamSynchronize failed!\n");
	}
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);
	printf("Singlestream Time taken : %3.1f ms\n", elapsedTime);
	cudaFreeHost(host_a);
	cudaFreeHost(host_b);
	cudaFreeHost(host_c);
	cudaFree(dev_a);
	cudaFree(dev_b);//165ms
	cudaFree(dev_c);
	cudaStreamDestroy(stream);
}
//���ú˺�����ⵥ����������ʱ���������������ʱ�䣬�Ƚ���Ч��
int mutistream()
{
	cudaDeviceProp prop;
	int whichDevice;
	cudaGetDevice(&whichDevice);
	cudaGetDeviceProperties(&prop, whichDevice);
	if (!prop.deviceOverlap)
	{
		printf("Device will not handle overlaps, so no speed up from streams.\n");
		return 0;
	}

	cudaEvent_t start, stop;
	float elapsedTime;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

	
	cudaStream_t stream0, stream1;
	cudaStreamCreate(&stream0);
	cudaStreamCreate(&stream1);

	int *host_a, *host_b, *host_c;
	int *dev0_a, *dev0_b, *dev0_c;
	int *dev1_a, *dev1_b, *dev1_c;

	//����cudaMalloc��������GPU�ڴ�
	cudaError_t cudaStatus;
	cudaStatus = cudaMalloc((void **)&dev0_a, N * sizeof(int));
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaMalloc dev0_a failed!\n");
	}

	cudaStatus = cudaMalloc((void **)&dev0_b, N * sizeof(int));
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaMalloc dev0_b failed!\n");
	}

	cudaStatus = cudaMalloc((void **)&dev0_c, N * sizeof(int));
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaMalloc dev0_c failed!\n");
	}

	cudaStatus = cudaMalloc((void **)&dev1_a, N * sizeof(int));
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaMalloc dev1_a failed!\n");
	}

	cudaStatus = cudaMalloc((void **)&dev1_b, N * sizeof(int));
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaMalloc dev1_b failed!\n");
	}

	cudaStatus = cudaMalloc((void **)&dev1_c, N * sizeof(int));
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaMalloc dev1_c failed!\n");
	}

	//����cudaHostAlloc���������̶��ڴ�
	cudaStatus = cudaHostAlloc((void **)&host_a, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaHostAlloc host_a failed!\n");
	}

	cudaStatus = cudaHostAlloc((void **)&host_b, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaHostAlloc host_b failed!\n");
	}

	cudaStatus = cudaHostAlloc((void **)&host_c, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaHostAlloc host_c failed!\n");
	}

	//������������
	for (int i = 0; i < FULL_DATA_SIZE; i++)
	{
		host_a[i] = i - N;
		host_b[i] = i;
	}

	for (int i = 0; i < FULL_DATA_SIZE; i += N * 2)
	{
		cudaStatus = cudaMemcpyAsync(dev0_a, host_a + i, N * sizeof(int), cudaMemcpyHostToDevice, stream0);
		if (cudaStatus != cudaSuccess)
		{
			printf("cudaMemcpyAsync0 a failed!\n");
		}

		cudaStatus = cudaMemcpyAsync(dev0_b, host_b + i, N * sizeof(int), cudaMemcpyHostToDevice, stream0);
		if (cudaStatus != cudaSuccess)
		{
			printf("cudaMemcpyAsync0 b failed!\n");
		}

		kernel << <N / GPUBLOCKNUM, GPUTHREADNUM, 0, stream0 >> >(dev0_a, dev0_b, dev0_c);

		cudaStatus = cudaMemcpyAsync(dev1_a, host_a + N + i, N * sizeof(int), cudaMemcpyHostToDevice, stream1);
		if (cudaStatus != cudaSuccess)
		{
			printf("cudaMemcpyAsync1 a failed!\n");
		}

		cudaStatus = cudaMemcpyAsync(dev1_b, host_b + N + i, N * sizeof(int), cudaMemcpyHostToDevice, stream1);
		if (cudaStatus != cudaSuccess)
		{
			printf("cudaMemcpyAsync1 b failed!\n");
		}

		kernel << <N / GPUBLOCKNUM, GPUTHREADNUM, 0, stream1 >> >(dev1_a, dev1_b, dev1_c);

		cudaStatus = cudaMemcpyAsync(host_c + i, dev0_c, N * sizeof(int), cudaMemcpyDeviceToHost, stream0);
		if (cudaStatus != cudaSuccess)
		{
			printf("cudaMemcpyAsync0 c failed!\n");
		}

		cudaStatus = cudaMemcpyAsync(host_c + N + i, dev1_c, N * sizeof(int), cudaMemcpyDeviceToHost, stream1);
		if (cudaStatus != cudaSuccess)
		{
			printf("cudaMemcpyAsync1 c failed!\n");
		}
	}
	
	cudaStatus = cudaStreamSynchronize(stream0);
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaStreamSynchronize0 failed!\n");
	}

	cudaStatus = cudaStreamSynchronize(stream1);
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaStreamSynchronize1 failed!\n");
	}
	kernel1 << <N / GPUBLOCKNUM, GPUTHREADNUM >> >(dev1_a, dev1_b, dev1_c);
	cudaStatus = cudaDeviceSynchronize();
	if (cudaStatus != cudaSuccess)
	{
		printf("cudaDeviceSynchronize failed!\n");
	}
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);
	printf("Mutistream Time taken : %3.1f ms\n", elapsedTime);

	cudaFreeHost(host_a);
	cudaFreeHost(host_b);
	cudaFreeHost(host_c);
	cudaFree(dev0_a);
	cudaFree(dev0_b);
	cudaFree(dev0_c);
	cudaFree(dev1_a);
	cudaFree(dev1_b);
	cudaFree(dev1_c);
	cudaStreamDestroy(stream0);
	cudaStreamDestroy(stream1);//162

	cudaProfilerStop();
	
	return 0;

}

int main0317()
{
	singlestream();
	mutistream();
	return 0;
}

/* ����������cuda_malloc_test������cuda_host_alloc_test�������й̶��ڴ�Ĳ���*/
int main1(int argc, char ** argv)
{
	float elapsedTime;
	float MB = (float)100 * size * sizeof(int) / 1024 / 1024;
	elapsedTime = cuda_malloc_test(size, true);
	printf("Time using cudaMalloc: %3.1f ms.", elapsedTime);
	printf("\tMB/s during copy up: %3.1f.\n", MB / (elapsedTime / 1000));
	elapsedTime = cuda_malloc_test(size, false);
	printf("Time using cudaMalloc: %3.1f ms.", elapsedTime);
	printf("\tMB/s during copy up: %3.1f.\n", MB / (elapsedTime / 1000));
	elapsedTime = cuda_host_alloc_test(size, true);
	printf("Time using cudaHostAlloc: %3.1f ms.", elapsedTime);
	printf("\tMB/s during copy up: %3.1f.\n", MB / (elapsedTime / 1000));
	elapsedTime = cuda_host_alloc_test(size, false);
	printf("Time using cudaHostAlloc: %3.1f ms.", elapsedTime);
	printf("\tMB/s during copy up: %3.1f.\n", MB / (elapsedTime / 1000));
	return 0;
}
