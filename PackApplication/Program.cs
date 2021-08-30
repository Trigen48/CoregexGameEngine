using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CoreGex.Assets;
namespace PackApplication
{
    class Program
    {

       
        static void Main(string[] args)
        {

            if (args == null || args.Length == 0)
            {
                return;
            }

            if (!System.IO.File.Exists(args[0]))
            {
                return;
            }

            string folder = "";
            string file = "temp.igp";


            string[] lines = System.IO.File.ReadAllLines(args[0]);
            exAssets asset = new exAssets();
            asset.CreateNewPack();

            foreach(string line in lines)
            {

                if (line.Replace(" ", "") == "")
                    continue;


                if (line.StartsWith("@"))
                {
                    string f = "";
                    if (line.StartsWith("@folder="))
                    {
                        f = line.Replace("@folder=", "").Trim();

                        if (System.IO.Directory.Exists(f))
                        {
                            folder = f;
                        }
                        
                    }
                    else if(line.StartsWith("@file="))
                    {
                        f = line.Replace("@file=", "").Trim();
                        file = f;
                    }

                    f = ""; 
                }
                else if(line.StartsWith("$"))
                {
                    string fi = line;
                    string entry = "";
                    
                    if (fi.Contains(">"))
                    {
                        string[] c=fi.Split(">".ToCharArray());
                        if(c.Length==2)
                        {
                            fi=c[0];
                            entry=c[1].Trim();
                        }
                    }

                    string fs=folder +fi.Trim().Substring(1);
                    if (System.IO.File.Exists(fs))
                    {
                        if (entry == "")
                        {
                            asset.AddFile(fs);
                        }
                        else
                        {
                            asset.AddFile(fs, entry);
                        }
                    }
                }

            }


            asset.Pack(file);
            asset.ClosePack();
            asset = null;

        }
    }
}
