char *text = "Mochi";

int main() {
    int length;

    length = strlen(text);

    return 0;
}

int strlen(char *s) {
    char *p = s;
    while (*p != '\0') p++;
    return p - s;
}