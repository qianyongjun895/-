# 算法说明

# 基础操作，读取图片，获得图片尺寸
  read_image (Image, 'E:/统一试题/图2.jpg')
  get_image_size (Image, Width, Height)

# 根据图片特征检测黄色元器件，分离三色通道
  decompose3 (Image, Image1, Image2, Image3)

# 三色通道灰度图片进行阈值
  threshold (Image1, Region, 240, 255)
  threshold (Image2, Region1, 240, 255)
  threshold (Image3, Region2, 240, 255)
  
# 不同颜色的灰度图片最差B-G（蓝色-绿色）
  region_to_bin (Region2, BinImage, 255, 0, Width, Height)
  region_to_bin (Region, BinImage1, 255, 0, Width, Height)
  abs_diff_image (BinImage1, BinImage, ImageAbsDiff, 1)

# 做差的图片进行阈值
   threshold (ImageAbsDiff, Region3, 128, 255)

# 阈值得到区域，做开运算
   opening_circle (Region3, RegionOpening, 3.5)

# 阈值得到的ROI区域进行筛选
  connection (RegionOpening, ConnectedRegions)
  select_shape (ConnectedRegions, SelectedRegions, 'area', 'or', 500, 99999)

# 对筛选后的区域做进一步筛选
  count_obj (SelectedRegions, Number) //获得区域的数量
 for i := 1 to Number by 1
    select_obj (SelectedRegions, ObjectSelected, i) //获取每个区域的对象
    smallest_rectangle2 (ObjectSelected, Row, Column, Phi, Length1, Length2) //获得每个区域的最小外接矩形smallest_rectangle2算子
    gen_rectangle2 (Rectangle1, Row, Column, Phi, Length1, Length2) //根据最小外接矩形，新建一个ROI区域
    smallest_rectangle1 (Rectangle1, Row1, Column1, Row2, Column2) //获取每个区域的最小外接矩形采用smallest_rectangle1
    gen_rectangle1 (Rectangle2, Row2, Column1, Row2+10, Column2) //根据smallest_rectangle1得到的最新外接矩形，获取平行于外接矩形，下面10个像素区域
    intensity (Rectangle2, Image2, Mean, Deviation) //获取平行于外接矩形，下面10个像素区域灰度平均值（当灰度平均值<70的时候判断不是有效的区域）
  endfor

# 最后一步的算法解释
  根据图片特征，有些元器件部分成像是黄色，整体元器件初黄色部分外，其他部分是黑色。所以在G（绿色）通道的灰度图片里面判断黄色区域周围是不是又黑色成像。
