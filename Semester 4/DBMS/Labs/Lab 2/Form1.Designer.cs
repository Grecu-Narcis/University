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
            this.ParentDataGrid = new System.Windows.Forms.DataGridView();
            this.ChildDataGrid = new System.Windows.Forms.DataGridView();
            this.parentLabel = new System.Windows.Forms.Label();
            this.childLabel = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.ParentDataGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ChildDataGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // ParentDataGrid
            // 
            this.ParentDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ParentDataGrid.Location = new System.Drawing.Point(47, 113);
            this.ParentDataGrid.Name = "ParentDataGrid";
            this.ParentDataGrid.RowHeadersWidth = 51;
            this.ParentDataGrid.RowTemplate.Height = 24;
            this.ParentDataGrid.Size = new System.Drawing.Size(455, 298);
            this.ParentDataGrid.TabIndex = 0;
            this.ParentDataGrid.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.ParentDataGrid_CellContentClick);
            // 
            // ChildDataGrid
            // 
            this.ChildDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ChildDataGrid.Location = new System.Drawing.Point(682, 113);
            this.ChildDataGrid.Name = "ChildDataGrid";
            this.ChildDataGrid.RowHeadersWidth = 51;
            this.ChildDataGrid.RowTemplate.Height = 24;
            this.ChildDataGrid.Size = new System.Drawing.Size(462, 298);
            this.ChildDataGrid.TabIndex = 1;
            // 
            // parentLabel
            // 
            this.parentLabel.AutoSize = true;
            this.parentLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.parentLabel.Location = new System.Drawing.Point(42, 74);
            this.parentLabel.Name = "parentLabel";
            this.parentLabel.Size = new System.Drawing.Size(75, 25);
            this.parentLabel.TabIndex = 2;
            this.parentLabel.Text = "Parent:";
            this.parentLabel.Click += new System.EventHandler(this.label1_Click);
            // 
            // childLabel
            // 
            this.childLabel.AutoSize = true;
            this.childLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.childLabel.Location = new System.Drawing.Point(677, 74);
            this.childLabel.Name = "childLabel";
            this.childLabel.Size = new System.Drawing.Size(57, 25);
            this.childLabel.TabIndex = 3;
            this.childLabel.Text = "Child";
            this.childLabel.Click += new System.EventHandler(this.label2_Click);
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
            this.Controls.Add(this.childLabel);
            this.Controls.Add(this.parentLabel);
            this.Controls.Add(this.ChildDataGrid);
            this.Controls.Add(this.ParentDataGrid);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.ParentDataGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ChildDataGrid)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView ParentDataGrid;
        private System.Windows.Forms.DataGridView ChildDataGrid;
        private System.Windows.Forms.Label parentLabel;
        private System.Windows.Forms.Label childLabel;
        private System.Windows.Forms.Button button1;
    }
}

