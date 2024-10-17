int main() {
    struct course {
        char *department;
        int number;
        char *name;
    };

    struct course my_courses[3] = {
        {"CSC", 225, "Introduction to Computer Organization"},
        {"CSC", 349, "Data Analysis and Algorithms"},
    };

    my_courses[2].department = "CSC";
    my_courses[2].number = 357;
    my_courses[2].name = "Systems Programming";
}
