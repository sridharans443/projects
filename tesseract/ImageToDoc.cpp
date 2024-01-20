#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include<fstream>
using namespace std;
int main()
{
    char *outText;

    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Pix *image = pixRead("/home/srii/Desktop/git_workspace/projects/tesseract/justified_text.png");
    api->SetPageSegMode(tesseract::PSM_AUTO);
    api->SetImage(image);
    
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);

    ofstream outputFile("/home/srii/Desktop/git_workspace/projects/tesseract/ocr_result.txt");

    if(outputFile.is_open()){
        outputFile<<outText;
        outputFile.close(); 
    }
    // Destroy used object and release memory
    api->End();
    delete api;
    delete [] outText;
    pixDestroy(&image);

    return 0;
}