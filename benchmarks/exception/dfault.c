#include "arch.h"
#include "benchmark.h"
#include "debug.h"
#include "harness.h"
#include "mem.h"

#define EXCEPTION_BENCHMARK_ITERATIONS 2500

static volatile uint32_t *ptr = (uint32_t*)0xc0000000;

__align12;

static void ALIGN kernel()
{
	uint64_t i, total_iterations = BENCHMARK_ITERATIONS * EXCEPTION_BENCHMARK_ITERATIONS;
	
	debug_spinner_start(EXCEPTION_BENCHMARK_ITERATIONS);
	
	for(i=0; i < total_iterations; ++i) {
		debug_spinner();
		*ptr;
	}
}

static void kernel_init()
{
	mem_init();
	mem_mmu_enable();
	mem_tlb_flush();
	
	arch_dfault_install_skip();
}
static void kernel_cleanup()
{
	mem_mmu_disable();
	mem_tlb_flush();
	mem_reset();
}

static benchmark_t bmark = {
	.name="Data-Fault",
	.category="Exception",
	.kernel_init=kernel_init,
	.kernel=kernel,
	.kernel_cleanup=kernel_cleanup,
	.iteration_count = EXCEPTION_BENCHMARK_ITERATIONS * BENCHMARK_ITERATIONS
};

REG_BENCHMARK(bmark);
