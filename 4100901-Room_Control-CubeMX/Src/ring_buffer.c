#include "ring_buffer.h"
/**
 * @brief Initialize the ring buffer.
 * @param rb Pointer to the ring buffer structure.
 * @param buffer Pointer to the buffer memory.
 * @param capacity Size of the buffer.
 */
void ring_buffer_init(ring_buffer_t *rb, uint8_t *buffer, uint16_t capacity) 
{
    rb->buffer = buffer;      // buffer: puntero al arreglo de datos del buffer circular
    rb->head = 0;             // head: índice donde se escribirá el próximo dato
    rb->tail = 0;             // tail: índice donde se leerá el próximo dato
    rb->capacity = capacity;  // capacity: tamaño máximo del buffer
    rb->is_full = false;      // is_full: indicador de si el buffer está lleno
}
/**
 * @brief Write data to the ring buffer, discard the old data if is full.
 * @param rb Pointer to the ring buffer structure.
 * @param data Data byte to write.
 * @retval true if the data was written successfully, false if the buffer is full.

 */
bool ring_buffer_write(ring_buffer_t *rb, uint8_t data)
{
    if (rb->is_full) {
        // If the buffer is full, overwrite the oldest data
        rb->tail = (rb->tail + 1) % rb->capacity; // Move tail forward
    }
    rb->buffer[rb->head] = data; // Write the data at the head position
    rb->head = (rb->head + 1) % rb->capacity; // Move head forward
    if (rb->head == rb->tail) {
        rb->is_full = true; // If head meets tail, buffer is full
    
    }

    return true;
}
/**
 * @brief Read data from the ring buffer.
 * @param rb Pointer to the ring buffer structure.
 * @param data Pointer to store the read data.
 * @retval true if data was read successfully, false if the buffer is empty.
 */

bool ring_buffer_read(ring_buffer_t *rb, uint8_t *data)
{
    if (rb->head == rb->tail && !rb->is_full) {
        // Buffer is empty
        return false;
    }

    *data = rb->buffer[rb->tail]; // Read the data at the tail position
    rb->tail = (rb->tail + 1) % rb->capacity; // Move tail forward
    rb->is_full = false; // Buffer is no longer full

    return true;
}
/**
 * @brief Get the number of elements in the ring buffer.
 * @param rb Pointer to the ring buffer structure.
 * @retval Number of elements in the buffer.
 */
uint16_t ring_buffer_count(ring_buffer_t *rb)
{
    if (rb->is_full) {
        return rb->capacity; // If the buffer is full, return the capacity
    }
    if (rb->head >= rb->tail) {
        return rb->head - rb->tail; // If head is ahead of tail, return the difference
    }
    return rb->capacity - rb->tail + rb->head; 
}
/**
 * @brief Check if the ring buffer is empty.
 * @param rb Pointer to the ring buffer structure.
 * @retval true if the buffer is empty, false otherwise.
 */


bool ring_buffer_is_empty(ring_buffer_t *rb)
{
    return (rb->head == rb->tail && !rb->is_full); // Buffer is empty if head equals tail and is_full is false
}
/**
 * @brief Check if the ring buffer is full.
 * @param rb Pointer to the ring buffer structure.
 * @retval true if the buffer is full, false otherwise.
 */

bool ring_buffer_is_full(ring_buffer_t *rb)
{
    return rb->is_full; // Buffer is full if is_full is true
}
/**
 * @brief Flush the ring buffer, resetting head and tail.
 * @param rb Pointer to the ring buffer structure.
 */

void ring_buffer_flush(ring_buffer_t *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->is_full = false;
}
/**
 * @brief Get the capacity of the ring buffer.
 * @param rb Pointer to the ring buffer structure.
 * @retval Capacity of the buffer.
 */
