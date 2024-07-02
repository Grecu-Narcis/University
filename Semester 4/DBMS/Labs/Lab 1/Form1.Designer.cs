namespace Lab_1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.UsersDataGrid = new System.Windows.Forms.DataGridView();
            this.PostsDataGrid = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.UsersDataGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.PostsDataGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // UsersDataGrid
            // 
            this.UsersDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.UsersDataGrid.Location = new System.Drawing.Point(47, 113);
            this.UsersDataGrid.Name = "UsersDataGrid";
            this.UsersDataGrid.RowHeadersWidth = 51;
            this.UsersDataGrid.RowTemplate.Height = 24;
            this.UsersDataGrid.Size = new System.Drawing.Size(455, 298);
            this.UsersDataGrid.TabIndex = 0;
            // 
            // PostsDataGrid
            // 
            this.PostsDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.PostsDataGrid.Location = new System.Drawing.Point(682, 113);
            this.PostsDataGrid.Name = "PostsDataGrid";
            this.PostsDataGrid.RowHeadersWidth = 51;
            this.PostsDataGrid.RowTemplate.Height = 24;
            this.PostsDataGrid.Size = new System.Drawing.Size(462, 298);
            this.PostsDataGrid.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(42, 74);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(63, 25);
            this.label1.TabIndex = 2;
            this.label1.Text = "Users";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(677, 74);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(61, 25);
            this.label2.TabIndex = 3;
            this.label2.Text = "Posts";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(553, 445);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 38);
            this.button1.TabIndex = 4;
            this.button1.Text = "Update";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1180, 525);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.PostsDataGrid);
            this.Controls.Add(this.UsersDataGrid);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.UsersDataGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.PostsDataGrid)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView UsersDataGrid;
        private System.Windows.Forms.DataGridView PostsDataGrid;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button1;
    }
}

