using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;

namespace TilemapGenerator
{
    class Program
    {
        public static int tileWidth = 16;
        public static int tileHeight = 16;

        public Dictionary<int, Bitmap> lstTileSet = new Dictionary<int, Bitmap>();
        public static string enviroment = System.Environment.CurrentDirectory;
        public string projectDirectory = Directory.GetCurrentDirectory();
        //public string projectDirectory = Directory.GetParent(enviroment).Parent.FullName;
        public static string InputFileName = "Map2Level2.png";
        public static string CsvFileName = "Map2Level2.csv";
        public static string OutputFileName = "Map2Level2-tileset.png";
        
        public bool Equals(Bitmap bmp1, Bitmap bmp2)
        {
            if (!bmp1.Size.Equals(bmp2.Size))
            {
                return false;
            }
            for (int x = 0; x < bmp1.Width; ++x)
            {
                for (int y = 0; y < bmp1.Height; ++y)
                {
                    if (bmp1.GetPixel(x, y) != bmp2.GetPixel(x, y))
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        public bool IsEqual(Bitmap bmp1, Bitmap bmp2)
        {
            if (object.Equals(bmp1, bmp2))
                return true;

            int bytes = bmp1.Width * bmp1.Height * (Image.GetPixelFormatSize(bmp1.PixelFormat) / 8) - 1;

            bool result = true;
            var b1bytes = new byte[bytes];
            var b2bytes = new byte[bytes];

            var bitmapData1 = bmp1.LockBits(new Rectangle(0, 0, bmp1.Width, bmp1.Height), ImageLockMode.ReadOnly, bmp1.PixelFormat);
            var bitmapData2 = bmp2.LockBits(new Rectangle(0, 0, bmp2.Width, bmp2.Height), ImageLockMode.ReadOnly, bmp2.PixelFormat);

            Marshal.Copy(bitmapData1.Scan0, b1bytes, 0, bytes);
            Marshal.Copy(bitmapData2.Scan0, b2bytes, 0, bytes);

            for (int n = 0; n < bytes; ++n)
            {
                if (b1bytes[n] != b2bytes[n])
                {
                    result = false;
                    break;
                }
            }

            bmp1.UnlockBits(bitmapData1);
            bmp2.UnlockBits(bitmapData2);

            return result;
        }
        public int AlreadyIncluded(Dictionary<int, Bitmap> source, Bitmap bitmap)
        {
            if (source.Count < 1)
            {
                return -1;
            }
            foreach (var b in source)
            {
                if (Equals(b.Value, bitmap))
                {
                    return b.Key;
                }
            }
            return -1;
        }
        public Bitmap CropTile(Bitmap source, Rectangle sourceRect)
        {
            // An empty bitmap which will hold the cropped image
            Bitmap bmp = new Bitmap(sourceRect.Width, sourceRect.Height);
            Rectangle destRect = new Rectangle(0, 0, tileWidth, tileHeight);

            using (Graphics g = Graphics.FromImage(bmp))
            {
                // Draw the given area (section) of the source image
                // at location 0,0 on the empty bitmap (bmp)
                g.DrawImage(source, destRect, sourceRect, GraphicsUnit.Pixel);
            }

            return bmp;
        }
        public void CreateTileFromPicture(string filePath)
        {
            filePath = Path.Combine(projectDirectory, filePath);
            if (!File.Exists(filePath))
            {
                Console.WriteLine("File Path Invalid");
                return;
            }

            if (!filePath.EndsWith(".png") && !filePath.EndsWith(".PNG"))
            {
                Console.WriteLine("File is not an image");
                return;
            }

            Bitmap img = new Bitmap(filePath);
            int numTilesWidth = img.Width / tileWidth;
            int numTilesHeight = img.Height / tileHeight;
            List<Bitmap> lstTiles = new List<Bitmap>();
            //cut image into species
            for (int row = 0; row < numTilesHeight; row++)
            {
                for (int col = 0; col < numTilesWidth; col++)
                {
                    Console.WriteLine($"[{row}][{col}]");
                    Rectangle sourceRect = new Rectangle(tileWidth * col, tileHeight * row, tileWidth, tileHeight);
                    lstTiles.Add(CropTile(img, sourceRect));
                }
            }
            if (lstTiles.Count <= 0)
            {
                Console.WriteLine("Could no cut into tiles");
                return;
            }

            //initialize
            lstTileSet.Clear();
            List<int> lstId = new List<int>();
            //Minimize
            int index = 0;
            int res = -1;
            Console.WriteLine("Total: " + lstTiles.Count);
            foreach (var tile in lstTiles)
            {
                Console.WriteLine(index);
                res = AlreadyIncluded(lstTileSet, tile);
                if (res == -1)
                {
                    lstTileSet.Add(index, tile);
                    lstId.Add(index);
                    index++;
                }
                else
                    lstId.Add(res);
            }
            //end write to file
            Console.WriteLine("Write to csv data file...");
            StreamWriter streamWriter = new StreamWriter(Path.Combine(projectDirectory, CsvFileName));
            streamWriter.Write(String.Join("\n", lstId));
            streamWriter.Close();


            //draw to image
            //calculate szie of image
            Console.WriteLine("Drawing tileset...");
            Bitmap finalImg = new Bitmap(tileWidth * lstTileSet.Count, tileHeight);
            //Bitmap finalImg = new Bitmap(numTilesWidth * 16, numTilesHeight * 16);
            using (Graphics g = Graphics.FromImage(finalImg))
            {
                g.Clear(Color.Black);
                for (int i = 0; i < lstTileSet.Count; i++)
                {
                    g.DrawImage(lstTileSet[i], new Rectangle(i * tileWidth, 0, tileWidth, tileHeight), new Rectangle(0, 0, tileWidth, tileHeight), GraphicsUnit.Pixel);
                }

                //for (int row = 0; row <= lstTileSet.Count / 2; row++)
                //{
                //    for (int col = 0; col <= lstTileSet.Count / 2; col++)
                //    {
                //        g.DrawImage(
                //            lstTiles.ElementAt(col + row * numTilesWidth), 
                //            new Rectangle(col * 16, row * 16,
                //            lstTiles.ElementAt(col + row * numTilesWidth).Width,
                //            lstTiles.ElementAt(col + row * numTilesWidth).Height));

                //    }
                //}

            }

            finalImg.Save(Path.Combine(projectDirectory, OutputFileName));


            //Bitmap finalImg02 = new Bitmap(16 * lstTileSet.Count / 2, 16);
            //using (Graphics g = Graphics.FromImage(finalImg02))
            //{
            //    g.Clear(Color.Black);
            //    for (int i = lstTileSet.Count / 2; i < lstTileSet.Count; i++)
            //    {
            //        g.DrawImage(lstTileSet[i], new Rectangle(i * 16, 0, 16, 16), new Rectangle(0, 0, 16, 16), GraphicsUnit.Pixel);
            //    }
            //}
            //finalImg02.Save(Path.Combine(projectDirectory, "dungeon_tileset_02.png"));

        }

        static void Main(string[] args)
        {
            try
            {
                Program program = new Program();

                string filename = InputFileName;
                Console.WriteLine("Prepare...");
                program.CreateTileFromPicture(filename);
                Console.WriteLine("Finished.");
                Console.ReadLine();
            }
            catch (Exception)
            {
                throw;
            }
        }
    }
}
