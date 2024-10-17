int main()
{
    char str1[] = "Hello";  // Automatically adds '\0'
    char str2[6] = "Hello";  // Explicit size (5 characters + '\0')
    char *str3 = "Hello";  // Pointer to string literal (read-only)
}