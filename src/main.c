#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

// Helper function to print a string element
void print_string(void *data) {
    printf("%s\n", (char*)data);
}

// Helper function to free a string element
void free_string(void *data) {
    free(data);
}

int main() {
    // Create a new vector
    vector_t *vec = vector(5);  // Initial capacity of 5
    
    // Set the free function for proper cleanup
    vec->free = free_string;
    
    printf("Initial vector state:\n");
    printf("Size: %zu\n", vector_size(vec));
    printf("Max size: %zu\n\n", vec->max_size);

    // Add some elements
    printf("Adding elements...\n");
    vector_push(vec, strdup("First"));
    vector_push(vec, strdup("Second"));
    vector_push(vec, strdup("Third"));
    vector_push(vec, strdup("Fourth"));
    vector_push(vec, strdup("Fifth"));
    vector_push(vec, strdup("Sixth"));  // This will trigger resize

    printf("\nVector after adding elements:\n");
    printf("Size: %zu\n", vector_size(vec));
    printf("Max size: %zu\n", vec->max_size);
    
    printf("\nPrinting all elements:\n");
    vector_print(vec, print_string);

    // Demonstrate get operation
    printf("\nGetting element at index 2:\n");
    char *element = vector_getAt(vec, 2);
    printf("Element at index 2: %s\n", element);

    // Demonstrate set operation
    printf("\nChanging element at index 2...\n");
    char *new_element = strdup("New Third");
    char *old_element = vector_getAt(vec, 2);
    free(old_element);  // Free the old string
    vector_setAt(vec, 2, new_element);

    printf("\nVector after modification:\n");
    vector_print(vec, print_string);

    // Demonstrate pop operation
    printf("\nPopping elements...\n");
    char *popped = vector_pop(vec);
    printf("Popped: %s\n", popped);
    free(popped);  // Don't forget to free the popped string

    printf("\nVector after popping:\n");
    printf("Size: %zu\n", vector_size(vec));
    printf("Max size: %zu\n", vec->max_size);
    vector_print(vec, print_string);

    // Test error handling
    printf("\nTesting out of bounds access:\n");
    element = vector_getAt(vec, 10);  // Should print error
    vector_setAt(vec, 10, "Test");    // Should print error

    // Clean up
    printf("\nCleaning up...\n");
    vector_clear(vec);
    vector_free(vec);
    free(vec);

    printf("Program completed successfully!\n");
    return 0;
}
