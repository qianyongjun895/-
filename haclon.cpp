#include "haclon.h"
#  include "HalconCpp.h"
#  include "HDevThread.h"

haclon::haclon()
{

}

haclon::action(QImage img)
{


    // Local iconic variables
     HObject  ho_Image, ho_Image1, ho_Image2, ho_Image3;
     HObject  ho_Region, ho_Region1, ho_Region2, ho_BinImage;
     HObject  ho_BinImage1, ho_ImageAbsDiff, ho_Region3, ho_RegionOpening;
     HObject  ho_ConnectedRegions, ho_SelectedRegions, ho_ObjectSelected;
     HObject  ho_Rectangle1, ho_Rectangle2;

     // Local control variables
     HTuple  hv_Width, hv_Height, hv_Number, hv_i;
     HTuple  hv_Row, hv_Column, hv_Phi, hv_Length1, hv_Length2;
     HTuple  hv_Row1, hv_Column1, hv_Row2, hv_Column2, hv_Mean;
     HTuple  hv_Deviation;

    // ReadImage(&ho_Image, "E:/统一试题/图2.jpg");

     GetImageSize(ho_Image, &hv_Width, &hv_Height);
     Decompose3(ho_Image, &ho_Image1, &ho_Image2, &ho_Image3);
     Threshold(ho_Image1, &ho_Region, 240, 255);
     Threshold(ho_Image2, &ho_Region1, 240, 255);
     Threshold(ho_Image3, &ho_Region2, 240, 255);
     RegionToBin(ho_Region2, &ho_BinImage, 255, 0, hv_Width, hv_Height);
     RegionToBin(ho_Region, &ho_BinImage1, 255, 0, hv_Width, hv_Height);
     AbsDiffImage(ho_BinImage1, ho_BinImage, &ho_ImageAbsDiff, 1);
     Threshold(ho_ImageAbsDiff, &ho_Region3, 128, 255);
     OpeningCircle(ho_Region3, &ho_RegionOpening, 3.5);
     Connection(ho_RegionOpening, &ho_ConnectedRegions);
     SelectShape(ho_ConnectedRegions, &ho_SelectedRegions, "area", "or", 500, 99999);
     CountObj(ho_SelectedRegions, &hv_Number);
     {
     HTuple end_val14 = hv_Number;
     HTuple step_val14 = 1;
     for (hv_i=1; hv_i.Continue(end_val14, step_val14); hv_i += step_val14)
     {
       SelectObj(ho_SelectedRegions, &ho_ObjectSelected, hv_i);
       SmallestRectangle2(ho_ObjectSelected, &hv_Row, &hv_Column, &hv_Phi, &hv_Length1,
           &hv_Length2);
       GenRectangle2(&ho_Rectangle1, hv_Row, hv_Column, hv_Phi, hv_Length1, hv_Length2);
       SmallestRectangle1(ho_Rectangle1, &hv_Row1, &hv_Column1, &hv_Row2, &hv_Column2);
       GenRectangle1(&ho_Rectangle2, hv_Row2, hv_Column1, hv_Row2+10, hv_Column2);
       Intensity(ho_Rectangle2, ho_Image2, &hv_Mean, &hv_Deviation);
     }
     }

}
