#include "picture.hpp"

Picture::Picture() : head(nullptr), tail(nullptr) {}

Picture::Picture(const Picture& other) {
    for (ListNode* node = other.head; node; node = node->next) {
        add(*node->shape);
    }
}

Picture::Picture(Picture&& other) : head(other.head), tail(other.tail) {
    other.head = nullptr;
    other.tail = nullptr;
}

void Picture::swap(Picture& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

Picture& Picture::operator=(const Picture& other) {
   if (this != &other) {
        Picture temp(other);
        swap(temp);
    }
    return *this;

}

Picture& Picture::operator=(Picture&& other) {
   swap(other);
    return *this;
}

/*void Picture::add(const Shape& shape) {
    Shape* clone = shape.clone();
    ListNode* node = new ListNode{ clone, nullptr };

    if (tail) {
        tail->next = node;
        tail = node;
    }
    else {
        head = tail = node;
    }
}*/
void Picture::add(const Shape& shape) {
    // Attempt to clone the shape
    Shape* clone = shape.clone();
    if (!clone) {
        // Error handling: Unable to clone shape
        std::cerr << "Error: Unable to clone shape." << std::endl;
        return;
    }

    // Create a new list node
    ListNode* node = new ListNode{ clone, nullptr };
    if (!node) {
        // Error handling: Memory allocation failed for list node
        delete clone; // Clean up cloned shape
        std::cerr << "Error: Memory allocation failed for list node." << std::endl;
        return;
    }

    // Insert the node into the list
    if (tail) {
        tail->next = node;
        tail = node;
    }
    else {
        head = tail = node;
    }
}


void Picture::print_all(std::ostream& out) const {
   for (ListNode* node = head; node; node = node->next) {
        node->shape->print(out);
        node->shape->draw(out);
    }
}

void Picture::draw_all(std::ostream& out) const {
    for (ListNode* node = head; node; node = node->next) {
        node->shape->draw(out);
    }
}

double Picture::total_area() const {
    double total = 0;
    for (ListNode* node = head; node; node = node->next) {
        total += node->shape->area();
    }
    return total;
}

Picture::~Picture() {
    while (head) {
        ListNode* next = head->next;
        delete head->shape;
        delete head;
        head = next;
    }
}
