﻿namespace _1104_이미지_실습_클라이언트
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.그림ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.그림목록보기ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.그림업로드하기ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.그림ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "mainMenu";
            // 
            // 그림ToolStripMenuItem
            // 
            this.그림ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.그림목록보기ToolStripMenuItem,
            this.그림업로드하기ToolStripMenuItem});
            this.그림ToolStripMenuItem.Name = "그림ToolStripMenuItem";
            this.그림ToolStripMenuItem.Size = new System.Drawing.Size(51, 24);
            this.그림ToolStripMenuItem.Text = "그림";
            // 
            // 그림목록보기ToolStripMenuItem
            // 
            this.그림목록보기ToolStripMenuItem.Name = "그림목록보기ToolStripMenuItem";
            this.그림목록보기ToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.그림목록보기ToolStripMenuItem.Text = "그림 목록 보기";
            this.그림목록보기ToolStripMenuItem.Click += new System.EventHandler(this.그림목록보기ToolStripMenuItem_Click);
            // 
            // 그림업로드하기ToolStripMenuItem
            // 
            this.그림업로드하기ToolStripMenuItem.Name = "그림업로드하기ToolStripMenuItem";
            this.그림업로드하기ToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.그림업로드하기ToolStripMenuItem.Text = "그림 업로드 하기";
            this.그림업로드하기ToolStripMenuItem.Click += new System.EventHandler(this.그림업로드하기ToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MainMenuStrip = this.menuStrip1;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.Text = "PictureClient";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 그림ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 그림목록보기ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 그림업로드하기ToolStripMenuItem;
    }
}

