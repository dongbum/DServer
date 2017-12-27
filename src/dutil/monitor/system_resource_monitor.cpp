#include "../define.h"

SystemResourceMonitor::DiskSpaceInfo SystemResourceMonitor::GetDiskSpaceInfo(std::string drive_name)
{
	DiskSpaceInfo disk_space_info;

	try
	{
		boost::filesystem::path path(drive_name.c_str());

		boost::filesystem::space_info space_info = boost::filesystem::space(path);

		disk_space_info.capacity = space_info.capacity;
		disk_space_info.free = space_info.free;
		disk_space_info.available = space_info.available;
	}
	catch (boost::filesystem::filesystem_error& ec)
	{
		LL_DEBUG("FileSystemError [%d] [%s]", ec.code(), ec.what())
	}

	return disk_space_info;
}

SystemResourceMonitor::MemoryInfo SystemResourceMonitor::GetMemoryInfo(void)
{
	MemoryInfo memory_info;

#ifdef _WIN32
	MEMORYSTATUSEX mem_status_info;
	mem_status_info.dwLength = sizeof(mem_status_info);
	::GlobalMemoryStatusEx(&mem_status_info);

	PROCESS_MEMORY_COUNTERS_EX pmce;
	::GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmce, sizeof(pmce));

	memory_info.phys_total = mem_status_info.ullTotalPhys;
	memory_info.phys_current_used = mem_status_info.ullTotalPhys - mem_status_info.ullAvailPhys;
	memory_info.phys_current_process = pmce.WorkingSetSize;

	memory_info.virtual_total = mem_status_info.ullTotalPageFile;
	memory_info.virtual_current_used = mem_status_info.ullTotalPageFile - mem_status_info.ullAvailPageFile;
	memory_info.virtual_current_process = pmce.PrivateUsage;

#endif

	return memory_info;
}
