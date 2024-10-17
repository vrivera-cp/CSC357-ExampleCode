typedef int _type;

#define CAPACITY_RESIZE_FACTOR  2

struct array_list {
    _type *data;
    int size;
    int capacity;
};

void copy_data(_type *source, _type *destination, int count) {
    for (int i = 0; i < count; i++) {
        *destination++ = *source++;
    }
}

void array_list_initialize(struct array_list *list, _type initial_data[], int initial_size) {
    list->data = malloc(sizeof(_type) * initial_size);
    
    copy_data(initial_data, list->data, initial_size);
    
    list->size = initial_size;
    list->capacity = initial_size;
}

void array_list_free(struct array_list *list) {
    free(list->data);
}

void array_list_increase_capacity(struct array_list *list) {
    list->capacity = list->capacity * CAPACITY_RESIZE_FACTOR;
    list->data = realloc(list->data, list->capacity * sizeof(_type));
}

void array_list_add(struct array_list *list, _type data) {
    if (list->size == list->capacity) {
        array_list_increase_capacity(list);
    }

    list->data[list->size++] = data;
}

void array_list_remove(struct array_list *list, int index) {
    if (index < 0 || index >= list->size) {
        return;
    }
    copy_data(&list->data[index + 1], &list->data[index], list->size - index - 1);
    list->size--;
}