using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;
using System.Diagnostics;
using System.Threading;

namespace CpuMemMonitor
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	/// 
    public class CPUMemMonitor : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Button btnAction;
		private System.Windows.Forms.TextBox txtFile;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.ComponentModel.IContainer components;
		private bool bAction;
		private Process proc;
		private System.Windows.Forms.NotifyIcon sysTray;
		private System.Windows.Forms.ContextMenu sysMenu;
		private System.Windows.Forms.MenuItem menuOpen;
		private System.Windows.Forms.MenuItem menuClose;
		private System.Windows.Forms.MenuItem menuExit;
		private System.Windows.Forms.MenuItem menuItem2;
		private Thread procThread;
		private bool doExit;
		public CPUMemMonitor()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();
			bAction = true;
			txtFile.Text = @"c:\File.txt";
			proc = new Process();
			proc.Exited += new EventHandler(proc_Exited);
			proc.EnableRaisingEvents = true;
			doExit = true;
			
			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(CPUMemMonitor));
			this.btnAction = new System.Windows.Forms.Button();
			this.txtFile = new System.Windows.Forms.TextBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.sysTray = new System.Windows.Forms.NotifyIcon(this.components);
			this.sysMenu = new System.Windows.Forms.ContextMenu();
			this.menuOpen = new System.Windows.Forms.MenuItem();
			this.menuClose = new System.Windows.Forms.MenuItem();
			this.menuExit = new System.Windows.Forms.MenuItem();
			this.menuItem2 = new System.Windows.Forms.MenuItem();
			this.SuspendLayout();
			// 
			// btnAction
			// 
			this.btnAction.Location = new System.Drawing.Point(24, 40);
			this.btnAction.Name = "btnAction";
			this.btnAction.TabIndex = 0;
			this.btnAction.Text = "Start";
			this.btnAction.Click += new System.EventHandler(this.btnAction_Click);
			// 
			// txtFile
			// 
			this.txtFile.Location = new System.Drawing.Point(128, 40);
			this.txtFile.Name = "txtFile";
			this.txtFile.Size = new System.Drawing.Size(256, 20);
			this.txtFile.TabIndex = 1;
			this.txtFile.Text = "";
			// 
			// groupBox1
			// 
			this.groupBox1.Location = new System.Drawing.Point(8, 8);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(400, 72);
			this.groupBox1.TabIndex = 2;
			this.groupBox1.TabStop = false;
			// 
			// sysTray
			// 
			this.sysTray.ContextMenu = this.sysMenu;
			this.sysTray.Icon = ((System.Drawing.Icon)(resources.GetObject("sysTray.Icon")));
			this.sysTray.Text = "CPU/Memory Monitor";
			this.sysTray.Visible = true;
			// 
			// sysMenu
			// 
			this.sysMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																					this.menuOpen,
																					this.menuClose,
																					this.menuItem2,
																					this.menuExit});
			// 
			// menuOpen
			// 
			this.menuOpen.Index = 0;
			this.menuOpen.Text = "Open";
			this.menuOpen.Click += new System.EventHandler(this.menuOpen_Click);
			// 
			// menuClose
			// 
			this.menuClose.Index = 1;
			this.menuClose.Text = "Close";
			this.menuClose.Click += new System.EventHandler(this.menuClose_Click);
			// 
			// menuExit
			// 
			this.menuExit.Index = 3;
			this.menuExit.Text = "Exit";
			this.menuExit.Click += new System.EventHandler(this.menuExit_Click);
			// 
			// menuItem2
			// 
			this.menuItem2.Index = 2;
			this.menuItem2.Text = "-";
			// 
			// CPUMemMonitor
			// 
			this.AutoScale = false;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(416, 93);
			this.Controls.Add(this.txtFile);
			this.Controls.Add(this.btnAction);
			this.Controls.Add(this.groupBox1);
			this.MaximizeBox = false;
			this.MaximumSize = new System.Drawing.Size(424, 120);
			this.MinimumSize = new System.Drawing.Size(424, 120);
			this.Name = "CPUMemMonitor";
			this.Text = "CPU/Memory Monitor";
			this.Closing += new System.ComponentModel.CancelEventHandler(this.CPUMemMonitor_Closing);
			this.Load += new System.EventHandler(this.CPUMemMonitor_Load);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new CPUMemMonitor());
		}

		private void btnAction_Click(object sender, System.EventArgs e)
		{
			if(bAction == true)
			{			
				try
				{
					ThreadStart st = new ThreadStart(Start);
					procThread = new Thread(st);
					procThread.Start();
					Thread.Sleep(2000);
					btnAction.Text = "Stop";
					bAction = false;
				}
				catch(Exception ex)
				{
					MessageBox.Show(ex.Message);
				}
			}
			else
			{
				try
				{
					Stop();
					bAction = true;
					btnAction.Text = "Start";
				}
				catch(Exception ex)
				{
					MessageBox.Show(ex.Message);
				}
				
			}
		}

		private void CPUMemMonitor_Load(object sender, System.EventArgs e)
		{
			if(bAction == true)
				btnAction.Text = "Start";
			else
				btnAction.Text = "Stop";
		}

		private void proc_Exited(object sender, EventArgs e)
		{
			try
			{
				btnAction.Text = "Start";
				bAction = true;
				Stop();
			}
			catch(Exception ex)
			{
				//MessageBox.Show(ex.Message);
			}
		}
		public void Start()
		{
			try
			{
				proc.StartInfo.FileName = @"Cpuusage.exe";
				proc.StartInfo.Arguments = @txtFile.Text;
				proc.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
				proc.Start();
				proc.WaitForExit();
			}
			catch(Exception ex)
			{
				throw ex;
			}
		}
		public void Stop()
		{
			if(procThread.ThreadState == System.Threading.ThreadState.Running)
				procThread.Abort();
			if(!proc.HasExited)
				proc.Kill();
	
		}

		private void menuOpen_Click(object sender, System.EventArgs e)
		{
			this.Show();
		}

		private void menuClose_Click(object sender, System.EventArgs e)
		{
			this.Hide();
		}

		private void menuExit_Click(object sender, System.EventArgs e)
		{
			doExit = false;
			this.Close();
		}

		private void CPUMemMonitor_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			e.Cancel = doExit;
			this.Hide();
			
		}
			
	}
}
