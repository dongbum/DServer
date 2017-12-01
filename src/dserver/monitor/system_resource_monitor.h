#pragma once

class SystemResourceMonitor
{
public:
	struct DiskSpaceInfo
	{
		DiskSpaceInfo(void)
		{
			memset(this, 0, sizeof(DiskSpaceInfo));
		};

		int64_t capacity;
		int64_t free;
		int64_t available;
	};

	struct MemoryInfo
	{
		MemoryInfo(void)
		{
			memset(this, 0, sizeof(MemoryInfo));
		};

		uint64_t phys_total;
		uint64_t phys_current_used;
		uint64_t phys_current_process;

		uint64_t virtual_total;
		uint64_t virtual_current_used;
		uint64_t virtual_current_process;
	};

	static DiskSpaceInfo GetDiskSpaceInfo(std::string drive_name);
	static MemoryInfo GetMemoryInfo(void);
private:
};