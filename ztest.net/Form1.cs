using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CoreGex.Engine;
using CoreGex.D2;
using CoreGex.Meshes;

namespace ztest.net
{
    public partial class Form1 : Form
    {

        Engine en;
        DeviceSettings st;
       // ColorModel mdl;
        Sprite sp;
        SpritesRaw rw;
        

        public Form1()
        {
            InitializeComponent();
        }

        private unsafe void Form1_Load(object sender, EventArgs e)
        {
            #region Display Setup
            st = new DeviceSettings();
            en = new Engine();
            st.Width = 1024;
            st.Height = 768;
            st.Windowed = true;
            st.Vertex = VertexProccesing.HardwareVertex;
            st.AdapterID = 0;
            st.AutoDepthStencilFormat = DisplayFormat.DF24X;
            st.DeviceMode = RenderMode.HardwareRender;
            st.Display = DisplayFormat.DF32X;
            st.RefreshRate = 60;
            st.EnableAutoDepthStencil = true;

            this.Width = 1024;
            this.Height = 768;
            this.BackColor = Color.Black;
            #endregion

            if (!en.InitEngine(this, st))
            {
                this.Close();
                return;

            }

            CoreGex.Assets.exAssets asset = new CoreGex.Assets.exAssets();
            asset.LoadPack("igs.irg");

            rw = new SpritesRaw();

            rw.AddNew();


            rw.LoadSprite(0, "test.png");
             sp = new Sprite();
           // mdl = new ColorModel();

            //mdl.Init();

            //asset.GetData(0, "test.png");
             float sk = sp.GetScaleX();

             if (!sp.IsLoaded())
             {
                 throw new Exception(); 
             }
             if (sk == 0)
             {
             }

             if (!sp.LoadSprite(asset.GetDataByte(0),asset.GetFileSize(0),1027,768))
            {
                throw new Exception(); 
            }

          /*  en.SetAmbientLighting(new CoreGex.Maths.TRLCOLOR(255, 255, 255, 255));
            en.TurnOnLighting(false);
            en.SetZEnable(true);*/

            timer1.Start();

        }


        private void timer1_Tick(object sender, EventArgs e)
        {
            en.Render();
           // mdl.Render();
            //rw.RenderSprite(0, 255);
            sp.RenderSprite(255);
            en.EndRender();
        }



    }
}
