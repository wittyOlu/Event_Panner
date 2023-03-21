afile = fopen("afile", "r");
    fread(str, sizeof(char), 400, afile);
    fclose(afile);
    ssp(str);
