#include<iostream>
#include<vector>
#include<string>
#include"bitmap.h"
using namespace std;

//function prototypes
void inputMax(int& max);
//call by reference to get the max user input
void getFirstFile(Bitmap& image);
//call by reference to get the user image file
void addPixels(vector <vector <Pixel> >& bmp, vector <vector <Pixel> >bmpCurrent);

//call by reference to have the updated pixels addition returned ... bmpCurrent is only used as call-by-value
int main()
{
        Bitmap image;
        vector <vector <Pixel> >bmp;

        //call the function to get the user maximum input
        int max;
        inputMax(max);

        //get the main file first, 1st file
        getFirstFile(image);

        //print the first image, store it's data
        cout<<"enter the first image"<<endl<<endl;
        bmp=image.toPixelMatrix();
        int rows=bmp.size();
        int cols=bmp[0].size();

        //begin with the valid image count as 1 " 1 image is done"
        int validImages=1;

        //now I can do the other files
        int row,column;
        //not less than two images
        for(int i=2;i<=max;i++)
        {
                Bitmap newImg;
                string fileName;
                cout<<"enter another image please: "<<endl;
                cin>>fileName;
                //read the file 
                newImg.open(fileName);

                /*then we need to know if the image is valid or not, and I made sure to contiue if it's not valid & to go to the image after it even if it's not valid*/
                // I wrote these invalid situations

                //ignore any invalid images files
                bool invalid=false;
                if(newImg.isImage())
                {
                        //for the valid images, generate pixel matrix
                        vector< vector<Pixel> >bmpCurrent;
                        bmpCurrent=newImg.toPixelMatrix();
                        int cRows=bmpCurrent.size();
                        //empty file is invalid
                        if(cRows==0)
                         
                                invalid=true;

                                if(!invalid)
                                {
                                        int cCols=bmpCurrent[0].size();

                                        // if rows and columns match the first image, then they are valid
                                        if(rows==cRows && cols==cCols)
                                        {
                                                //increment valid images count
                                                validImages++;
                                                //add pixels of valid images
                                                addPixels(bmp, bmpCurrent);
                                                //print occasional progress updates
                                                cout<<"Image "<<i<<" of "<<max<<" are done."<<endl;
                                        }
                                        else //didn't match then invalid
                                                invalid=true;
                                
                        }
                        else //file deos not exist
                        {
                                invalid=true;
                        }
                }
                //to print invalid results
                if(invalid)
                {
                        cout<<"Invalid bmp image"<<i<<endl;
                }
                //cout<<endl;
        
}        

//if only 1 image is valid then we can't composite the image so we print invalid
if(validImages == 1)
{
        cout<<"Can't create composite images because 1 image file is valid."<<endl;
}

//if more than 1 valid images, we should average out the RGB values and print the Composite images
else 
{
        for(int i=0;i<rows;i++)
        {
                for(int j=0;j<cols;j++)
                {
                        bmp[i][j].red=bmp[i][j].red/validImages;
                        bmp[i][j].green=bmp[i][j].green/validImages;
                        bmp[i][j].blue=bmp[i][j].blue/validImages;
                }
        }

        //now I can put image back into matrix, and update bitmap and save it
        image.fromPixelMatrix(bmp);
        image.save("compositeimage.bmp");

        cout<<"succesfully created created a composite image: compositeimage.bmp"<<endl;
}
        return 0;
}

// functions begin
//get the maximum number of files, must be between 2 and 10
void inputMax(int& max)
{
 
        max=0;
        do
{
        cout<<"enter the maximum number of files. Must be between 2 and 10 please: "<<endl;
        cin>>max;
}
        while(max<2);
        cout<<endl;

}
//asks the user to enter valid image file
void getFirstFile(Bitmap& image)
{
        string fileName;
        do{
                cout<<"Enter a valid first image file please: ";
                        cin>>fileName;
                //read the file
                image.open(fileName);
                //verify that the file opened was a valid image
        } while(!image.isImage());
}

//Combined the valid images together to make a composite image. The composite image should take the average value of RGB components for each pixel at the same location.
//add each bmpCurrent on the bmp
//the updated bmp is called back as call by reference peremeter
void addPixels(vector <vector <Pixel> >& bmp, vector <vector <Pixel> >bmpCurrent)

{
        for(int i=0;i<bmp.size();i++)
        {
                for(int j=0;j<bmp[i].size();j++)
                {
                        bmp[i][j].red+=bmpCurrent[i][j].red;
                        bmp[i][j].green+=bmpCurrent[i][j].green;
                        bmp[i][j].blue+=bmpCurrent[i][j].blue;
                }
        }
}
