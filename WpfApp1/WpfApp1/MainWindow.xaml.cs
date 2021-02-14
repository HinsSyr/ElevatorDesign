using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;




namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
       
        public class elevator
        {
         
            public double e_cloumngap { set; get; } = columngap;
            public double e_heightgap { set; get; } = heightgap;
            public double top { set; get; } = 610; // floor 1;
            public double left { set; get; } = 800;// first elevator;
            
            public elevator(int number) { left = 800 + number * columngap; }

        }

        public static double Width = System.Windows.SystemParameters.PrimaryScreenWidth;
        public static double height = System.Windows.SystemParameters.PrimaryScreenHeight;
        public static double columngap = (Width - 1000) / 3;
        public static double heightgap = 20;
        public List<elevator> elevators = new List<elevator>();
        public List<Rectangle> Rectangles = new List<Rectangle>();
      
        Dictionary<int,Rectangle> light_rec= new Dictionary<int,Rectangle>();
        Dictionary<int, Rectangle> arv_rec = new Dictionary<int, Rectangle>();
        public MainWindow()
        {
            InitializeComponent();
            this.WindowState = WindowState.Maximized;


            draw_lines(Width, height, columngap, heightgap);


            for (int i = 0; i < 3; i++)
            {

                elevator temp = new elevator(i);
                elevators.Add(temp);
                Rectangle rec = new Rectangle();
                Rectangles.Add(rec);
            }
            draw_elevator( Width, height, columngap, heightgap);

        }

        void draw_lines(double systemwidth, double systemheight, double widthgap, double heightgap)
        {

            Console.WriteLine(systemwidth);
            Console.WriteLine(systemheight);

            double increrow = 0;
            double increcolumn = 0;
            List<Line> rowlines = new List<Line>();
            List<Line> columnlines = new List<Line>();

            for (int i = 0; i < 31; i++)
            {

                Line line = new Line();
                rowlines.Add(line);
            }

            for (int i = 0; i < 4; i++)
            {
                Line line = new Line();
                columnlines.Add(line);
            }

            foreach (Line temp in columnlines)
            {

                temp.X1 = 800 + increcolumn;
                temp.X2 = 800 + increcolumn;

                temp.Y1 = 30;
                temp.Y2 = 630;

                increcolumn += widthgap;

                temp.StrokeThickness = 2;

                temp.Stroke = System.Windows.Media.Brushes.Black;
                temp.Visibility = System.Windows.Visibility.Visible;
                Grid_.Children.Add(temp);
            }
            foreach (Line temp in rowlines)
            {

                temp.X1 = 800;
                temp.X2 = systemwidth - 800;

                temp.Y1 = 30 + increrow;
                temp.Y2 = 30 + increrow;

                increrow += heightgap;

                temp.StrokeThickness = 2;

                temp.Stroke = System.Windows.Media.Brushes.Black;
                temp.Visibility = System.Windows.Visibility.Visible;
                Grid_.Children.Add(temp);
            }

            test();
        }



        void draw_elevator( double systemwidth, double systemheight, double widthgap, double heightgap)
        {
            for(int i= 0;i<3;i++)
            {
               
               
                Rectangles[i].Width = elevators[i].e_cloumngap;
                Rectangles[i].Height = elevators[i].e_heightgap;
                Rectangles[i].Fill = Brushes.Yellow;
                Rectangles[i].StrokeThickness = 2;
                Rectangles[i].Visibility = System.Windows.Visibility.Visible;

                Canvas.SetLeft(Rectangles[i], elevators[i].left);
                Canvas.SetTop(Rectangles[i], elevators[i].top);
                Canvas_.Children.Add(Rectangles[i]);

               

            }

        }

        private void test()
        {
           
            List<int> floors1 = new List<int>();
            string line;
            System.IO.StreamReader sr = new System.IO.StreamReader("../../../Project1/floor1.txt");
            while ((line = sr.ReadLine()) != null)
            {
                floors1.Add(Int32.Parse(line));
            }

            List<int> floors2 = new List<int>();
            string line2;
            System.IO.StreamReader sr2 = new System.IO.StreamReader("../../../Project1/floor2.txt");
            while ((line2 = sr2.ReadLine()) != null)
            {
                floors2.Add(Int32.Parse(line2));

            }

            List<int> floors3 = new List<int>();
            string line3;
            System.IO.StreamReader sr3 = new System.IO.StreamReader("../../../Project1/floor3.txt");
            while ((line3 = sr3.ReadLine()) != null)
            {
                floors3.Add(Int32.Parse(line3));
            }


            List<int> requests1 = new List<int>();
            string res;
            System.IO.StreamReader rs = new System.IO.StreamReader("../../../Project1/req1.txt");
            while ((res = rs.ReadLine()) != null)
            {
                requests1.Add(Int32.Parse(res));
            }

            List<int> requests2 = new List<int>();
            string res2;
            System.IO.StreamReader rs2 = new System.IO.StreamReader("../../../Project1/req2.txt");
            while ((res2 = rs2.ReadLine()) != null)
            {
                requests2.Add(Int32.Parse(res2));
            }

            List<int> requests3 = new List<int>();
            string res3;
            System.IO.StreamReader rs3 = new System.IO.StreamReader("../../../Project1/req3.txt");
            while ((res3 = rs3.ReadLine()) != null)
            {
                requests3.Add(Int32.Parse(res3));
            }

            List<int> arivals1 = new List<int>();
            string arv1;
            System.IO.StreamReader rav1 = new System.IO.StreamReader("../../../Project1/arv1.txt");
            while ((arv1 = rav1.ReadLine()) != null)
            {
                arivals1.Add(Int32.Parse(arv1));
            }

            List<int> arivals2 = new List<int>();
            string arv2;
            System.IO.StreamReader rav2 = new System.IO.StreamReader("../../../Project1/arv2.txt");
            while ((arv2 = rav2.ReadLine()) != null)
            {
                arivals2.Add(Int32.Parse(arv2));
            }

            List<int> arivals3 = new List<int>();
            string arv3;
            System.IO.StreamReader rav3 = new System.IO.StreamReader("../../../Project1/arv3.txt");
            while ((arv3 = rav3.ReadLine()) != null)
            {
                arivals3.Add(Int32.Parse(arv3));
            }

            DispatcherTimer delay;
            delay = new DispatcherTimer(DispatcherPriority.Normal);
            delay.Interval = TimeSpan.FromMilliseconds(500);
            delay.Tick += new EventHandler((sender2, e2) => delay_Tick(sender2, e2, floors1, floors2, floors3));
            delay.Start();

            DispatcherTimer lighttimer;
            lighttimer = new DispatcherTimer(DispatcherPriority.Normal);
            lighttimer.Interval = TimeSpan.FromMilliseconds(500);
            lighttimer.Tick += new EventHandler((sender2, e2) => light_tick(sender2, e2, requests1, requests2, requests3));
            lighttimer.Start();

            DispatcherTimer arvtimer;
            arvtimer = new DispatcherTimer(DispatcherPriority.Normal);
            arvtimer.Interval = TimeSpan.FromMilliseconds(500);
            arvtimer.Tick += new EventHandler((sender2, e2) => arv_light(sender2, e2, arivals1, arivals2, arivals3));
            arvtimer.Start();

        }

        private void arv_light(object sender, EventArgs e, List<int> arivals1, List<int> arivals2, List<int> arivals3)
        {
            if (arivals1.Count != 0)
            {
                arv_light_move(arivals1.First(), 0, heightgap);
                    arivals1.RemoveAt(0);
            }
            if (arivals2.Count != 0)
            {
                arv_light_move(arivals2.First(), 0, heightgap);
                    arivals2.RemoveAt(0);
            }
            if (arivals3.Count != 0)
            {
                arv_light_move(arivals3.First(), 0, heightgap);
                    arivals3.RemoveAt(0);
            }

            if(arivals1.Count == 0&& arivals2.Count == 0 && arivals3.Count == 0)
                 ((System.Windows.Threading.DispatcherTimer)sender).Stop();
        }

        private void light_tick(object sender, EventArgs e, List<int> reqs,List<int> reqs2,List<int> reqs3)
        {
            if (reqs.Count != 0)
            {
                request_light(reqs.First(), 0,heightgap);
                reqs.RemoveAt(0);
            }
            if (reqs2.Count != 0)
            {
                request_light(reqs2.First(),1, heightgap);
                reqs2.RemoveAt(0);
            }
            if (reqs3.Count != 0)
            {
                request_light(reqs3.First(),2, heightgap);
                reqs3.RemoveAt(0);
            }
            if ( reqs.Count == 0 && reqs2.Count==0 && reqs3.Count==0)
                ((System.Windows.Threading.DispatcherTimer)sender).Stop();
        }

        private void delay_Tick(object sender, EventArgs e, List<int> floors1, List<int> floors2, List<int> floors3)
        {
            if (floors1.Count != 0)
            {
                elevator_move(0, floors1.First(), heightgap);
                floors1.RemoveAt(0);
            }
            if (floors2.Count != 0)
            {
                elevator_move(1, floors2.First(), heightgap);
                floors2.RemoveAt(0);
            }
            if (floors3.Count != 0)
            {
                elevator_move(2, floors3.First(), heightgap);
                floors3.RemoveAt(0);
            }
          
            if (floors1.Count == 0 && floors2.Count == 0 && floors3.Count == 0  )
                ((System.Windows.Threading.DispatcherTimer)sender).Stop();


        }

        void arv_light_move(int floor, int number, double heightgap)
        {
            if (floor > 0)
            {
                double destx = heightgap * (30 - floor) + 30;
                if (!arv_rec.ContainsKey(floor))
                {
                    Rectangle rec = new Rectangle();
                    rec.Width = 30;
                    rec.Height = heightgap;
                    rec.Fill = Brushes.Blue;
                    rec.StrokeThickness = 2;
                    rec.Visibility = System.Windows.Visibility.Visible;
                    Canvas.SetLeft(rec, 700);
                    Canvas.SetTop(rec, destx);
                    arv_rec[floor] = rec;
                    Canvas_.Children.Add(rec);
                }
            }
            else if(floor<0)
            {

                Canvas_.Children.Remove(arv_rec[0 - floor]);
            }
            
        }

        void request_light(int floor, int number,double heightgap)
        {
            if (floor > 0)
            {
                double destx = heightgap * (30 - floor) + 30;
                if (!light_rec.ContainsKey(floor))
                {
                    Rectangle rec = new Rectangle();
                    rec.Width = 30;
                    rec.Height = heightgap;
                    rec.Fill = Brushes.Red;
                    rec.StrokeThickness = 2;
                    rec.Visibility = System.Windows.Visibility.Visible;
                    Canvas.SetLeft(rec, 750);
                    Canvas.SetTop(rec, destx);
                    light_rec[floor] = rec;
                    Canvas_.Children.Add(rec);
                }

            }
            else if(floor<0){
                Canvas_.Children.Remove(light_rec[0 - floor]);
            }
        }


    



    void elevator_move(int number, int destination, double heightgap)
        {

            Console.WriteLine(elevators[number].top);

            int current_floor = Convert.ToInt32(30 - (elevators[number].top - 30) / heightgap);
            Console.WriteLine(current_floor);
            int gap = destination - current_floor;
            double destx = heightgap * (30 - destination) + 30;
            Console.WriteLine(gap);


            if (gap > 0) //go up
            {
                Canvas_.Children.Remove(Rectangles[number]);

                elevators[number].top -= heightgap;

                Console.WriteLine(elevators[number].top);
                Console.WriteLine(destx);
                Canvas.SetLeft(Rectangles[number], elevators[number].left);
                Canvas.SetTop(Rectangles[number], elevators[number].top);

                Canvas_.Children.Add(Rectangles[number]);
              
            }
            else
            { // go down

                Canvas_.Children.Remove(Rectangles[number]);

                elevators[number].top += heightgap;

                Console.WriteLine(elevators[number].top);

                Canvas.SetLeft(Rectangles[number], elevators[number].left);
                Canvas.SetTop(Rectangles[number], elevators[number].top);

                Canvas_.Children.Add(Rectangles[number]);
             
            }
        }

        
    }


}
