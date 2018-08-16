#include <vsg/vk/MemoryManager.h>
#include <vsg/vk/Buffer.h>
#include <vsg/vk/Image.h>

#include <cstring>

// Useful links:
//    AMD's Vulan Device Memory discussion : https://gpuopen.com/vulkan-device-memory/
//    NVIDIA's Vulkan Memory Management  : https://developer.nvidia.com/vulkan-memory-management
//
// General comments
//
// Deivce local resources - use VkMemoryPropertyFlags of VK_DEVICE_LOCAL and not HOST_VISIBLE
//
// If Divice local allocations fail fallbac to HOST_VISIBLE with HOST_COHERENT but without HOST_CACHED
//
// Allocate high prioroty resources first i.e. Render Targets, then lower priotity objects
//
// On Window resizes be prepared to free all resources, then reallocated high priority ones
//
// CPU->GPU data flow Use DEVICE_LOCAL with HOST_VISIBLE for cases where you want to update Device local memory, ie. updloading constant data, keep allocation sizes below 256MB)
//
// GPU->CPU data flow use HOST_VISIBLE with HOST_COHERENT and HOST_CACHED, only memory type that supports cached reads by the CPU.  Screen captures, compute results etc.
//
// Pool resources as OS Window allocations can be expensive, place buffers and textures in single pools, 256MB is reasonalbe base
//


namespace vsg
{

MemoryManager::MemoryManager(Device* device, AllocationCallbacks* allocator) :
    _device(device),
    _allocator(allocator)
{
}

MemoryManager::~MemoryManager()
{
}

Buffer* MemoryManager::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkSharingMode sharingMode)
{
    ref_ptr<Buffer> buffer = Buffer::create(_device, size, usage, sharingMode, _allocator);
    return buffer.release();
}

DeviceMemory* MemoryManager::createMemory(const VkMemoryRequirements& memRequirements, VkMemoryPropertyFlags properties)
{
    ref_ptr<DeviceMemory> memory = DeviceMemory::create(_device, memRequirements, properties, _allocator);
    return memory.release();
}


}
