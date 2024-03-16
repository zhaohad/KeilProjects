#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include<iostream>  

using namespace std;
using namespace cv;

#define LEN_12864_ROW 8
#define LEN_12864_COL 128

int main()
{
    freopen("./out.txt", "w", stdout);
    Mat image = imread("eye128_64.png", IMREAD_GRAYSCALE);
    // Mat image = imread("1.png", IMREAD_GRAYSCALE);
    // Mat image = imread("Panda.jpg", IMREAD_GRAYSCALE);

    int rows = image.rows;
    int cols = image.cols;
    printf("rows = %d, cols = %d\n", rows, cols);

    uchar buf[LEN_12864_ROW][LEN_12864_COL];
    memset(buf, 0, sizeof(buf));

    for (int r = 0; r < rows; r++) {
        uchar* sptr = image.ptr<uchar>(r);
        for (int c = 0; c < cols; c++) {
            uchar ch = sptr[c];
            if (ch > (0xff / 2 * 1)) {
                sptr[c] = 0;
            }
            else {
                sptr[c] = 0xff;
            }

            char index = r / 8;
            char bufc = buf[index][c];
            if (sptr[c]) {
                buf[index][c] |= (1 << (r % 8));
            }
        }
    }

    for (int r = 0; r < LEN_12864_ROW; r++) {
        const uchar* sptr = buf[r];
        for (int c = 0; c < LEN_12864_COL; c++) {
            uchar ch = sptr[c];
            printf("0x%x, ", ch);
        }
        printf("\n");
    }

    imshow("Show Window", image);
    waitKey(0);
    return 0;
}