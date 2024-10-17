int main() {
    char *cats[3];
    
    *cats = "Mochi";
    cats[1] = "Harvest";
    *(cats + 2) = "Pearl";

    return 0;
}