#include <vsg/vk/Framebuffer.h>

#include <iostream>

namespace vsg
{

Framebuffer::Framebuffer(VkFramebuffer framebuffer, Device* device, AllocationCallbacks* allocator) :
    _framebuffer(framebuffer),
    _device(device),
    _allocator(allocator)
{
}

Framebuffer::~Framebuffer()
{
    if (_framebuffer)
    {
        std::cout<<"Calling vkDestroyFramebuffer"<<std::endl;
        vkDestroyFramebuffer(*_device, _framebuffer, *_allocator);
    }
}

Framebuffer::Result Framebuffer::create(Device* device, VkFramebufferCreateInfo& framebufferInfo, AllocationCallbacks*  allocator)
{
    if (!device)
    {
        return Result("Error: vsg::Framebuffer::create(...) failed to create Framebuffer, undefined Device.", VK_ERROR_INVALID_EXTERNAL_HANDLE);
    }

    VkFramebuffer framebuffer;
    VkResult result = vkCreateFramebuffer(*device,&framebufferInfo, *allocator, &framebuffer);
    if (result == VK_SUCCESS)
    {
        return new Framebuffer(framebuffer, device, allocator);
    }
    else
    {
        return Result("Error: vsg::Framebuffer::create(...) Failed to create VkFramebuffer.", result);
    }

}

}