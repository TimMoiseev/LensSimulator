using LensSimulator.Model.Lens;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace LensSimulator.Model.Graphics
{
    
    internal class MessageProcessingSystem
    {
        public struct OnOffCommand
        {
            public string Type { get { return "OnOffCommand"; } }
            public string CommandType { get; set; }
            public float Priority { get; set; }
        }
        [JsonConverter(typeof(JsonStringEnumConverter))]
        public enum ChangeLensMessageType
        {
            Add,
            Change,
            Delete
        }
        public struct ChangeLensMessage
        {
            public string Type { get { return "ChangeLensMessage"; } }
            public ChangeLensMessageType MessageType { get; set; }
            public int ID { get; set; }
            public LensModel.LensTypes LensType { get; set; }
            public float D { get; set; }
            public float R1 { get; set; }
            public float R2 { get; set; }
            public float H { get; set; }
            public float X { get; set; }
            public float Y { get; set; }
            public float Z { get; set; }
            public float Priority { get; set; }
        }

        [DllImport("C:\\Users\\lglgl\\Documents\\GitHub\\LensSimulator\\x64\\Debug\\GraphicsEngine.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        static protected extern IntPtr createMessageProcessingSystem();
        [DllImport("C:\\Users\\lglgl\\Documents\\GitHub\\LensSimulator\\x64\\Debug\\GraphicsEngine.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        private static protected extern void reciveMessageInternal(IntPtr target, string message);
        private static MessageProcessingSystem instance;
        IntPtr handle = IntPtr.Zero;
        private MessageProcessingSystem()
        {
            handle = createMessageProcessingSystem();
        }
        public static MessageProcessingSystem getSystem()
        {
            if (instance == null)
            {
                instance = new MessageProcessingSystem();
            }
            return instance;
        }
        public void transmitMessage(string message)
        {
            reciveMessageInternal(handle, message);
        }
    }
}
