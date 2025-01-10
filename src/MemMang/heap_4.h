#pragma once
#include <stddef.h>
#include <stdint.h>

struct xHeapStats;

namespace freertos
{
    /// @brief 空闲内存块链表节点。
    struct BlockLink_t
    {
        /// @brief 下一个空闲内存块。
        BlockLink_t *_next_free_block{};

        /// @brief 空闲内存块大小。
        size_t _size{};
    };

    /// @brief 基于 freertos 的 heap4 的堆管理器。
    class Heap4
    {
    private:
        /// @brief 将被释放的内存插入链表。
        /// @note 如果发现与链表中要插入位置的前一个节点和后一个节点指向的内存是连续的，会合并这些节点。
        /// @param pxBlockToInsert
        void InsertBlockIntoFreeList(freertos::BlockLink_t *pxBlockToInsert);

    public:
        /// @brief 构造一个基于 freertos 的 heap4 的堆管理器。
        /// @param buffer 要被作为堆的缓冲区。
        /// @param size 缓冲区大小。
        Heap4(uint8_t *buffer, size_t size);

        /* Create a couple of list links to mark the start and end of the list. */
        BlockLink_t xStart;
        BlockLink_t *pxEnd = nullptr;

        /* Keeps track of the number of calls to allocate and free memory as well as the
         * number of free bytes remaining, but says nothing about fragmentation. */
        size_t xFreeBytesRemaining = 0U;
        size_t xMinimumEverFreeBytesRemaining = 0U;
        size_t xNumberOfSuccessfulAllocations = 0;
        size_t xNumberOfSuccessfulFrees = 0;

        void *Malloc(size_t xWantedSize);
        void Free(void *pv);
        void *Calloc(size_t xNum, size_t xSize);
        void GetHeapStats(xHeapStats *pxHeapStats);
    };

} // namespace freertos
