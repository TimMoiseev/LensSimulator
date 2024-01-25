using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace LensSimulator.Model.Lens
{
    public class LensModel : INotifyPropertyChanged
    {
        [JsonConverter(typeof(JsonStringEnumConverter))]
        public enum LensTypes
        {
            DoubleConvexLens = 0,
            PlanoConvexLens = 1,
            PositiveMeniscusLens = 2,
            NegativeMeniscusLens = 3,
            PlanoConcaveLens = 4,
            DoubleConcaveLens = 5
        }
        
        private int? _id = null;
        public int Id { get {
                if(_id == null)
                {
                    _id = GetRandInt();
                    return (int)_id;
                }
                else
                {
                    return (int)_id;
                }
            }
        }

        private LensTypes _type;
        public LensTypes LensType
        {
            get { return _type; }
            set { _type = value; OnPropertyChanged(nameof(LensType)); }
        }
        private  double _r1;
        public double R1
        {
            get { return _r1; }
            set { _r1 = value; OnPropertyChanged(nameof(R1)); }
        }
        private double _r2;
        public double R2
        {
            get { return _r2; }
            set { _r2 = value; OnPropertyChanged(nameof(R2)); }
        }
        private double _h;
        public double H
        {
            get { return _h; }
            set { _h = value; OnPropertyChanged(nameof(H)); }
        }
        private double _d;
        public double D
        {
            get { return _d; }
            set { _d = value; OnPropertyChanged(nameof(D)); }
        }
        private double _x;
        public double X
        {
            get { return _x; }
            set { _x = value; OnPropertyChanged(nameof(X)); }
        }
        private double _y;
        public double Y
        {
            get { return _y; }
            set { _y = value; OnPropertyChanged(nameof(Y)); }
        }
        private double _z;
        public double Z
        {
            get { return _z; }
            set { _z = value; OnPropertyChanged(nameof(Z)); }
        }
        public LensModel(LensTypes type, double r1 = 25.0, double r2 = 25.0, double h = 10.0, double d = 30.0, double x = 0.0, double y = 0.0, double z = 0.0)
        {
            _type = type;
            _r1 = r1;
            _r2 = r2;
            _h = h;
            _d = d;
            _x = x;
            _y = y;
            _z = z;
        }
        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
        }
        private static int GetRandInt()
        {
            Random random = new Random();
            return random.Next(int.MinValue, int.MaxValue);
        }
    }
}
