
namespace Platform
{
	void* AllocAligned(size_t size, size_t alignment)
	{
		return _aligned_malloc(size, alignment);
	}

	void Free(void* memory)
	{
		_aligned_free(memory);
	}
}