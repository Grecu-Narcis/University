import { Component } from '@angular/core';
import { BackendService } from '../../services/BackendService';
import { ActivatedRoute, Router, RouterModule } from '@angular/router';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-edit-product-page',
  standalone: true,
  imports: [FormsModule, RouterModule],
  templateUrl: './edit-product-page.component.html',
  styleUrl: './edit-product-page.component.css'
})
export class EditProductPageComponent {
  productId: number = 0;
  name: string = '';
  price: number = 0;
  description: string = '';
  category: string = '';

  constructor(private backendService: BackendService, private route: ActivatedRoute, private router: Router) { }

  ngOnInit(): void {
    this.productId = parseInt(this.route.snapshot.paramMap.get('id')!);
    this.backendService.getProductById(this.productId).subscribe((data: any) => {
      this.name = data.name;
      this.price = data.price;
      this.description = data.description;
      this.category = data.category;
    });
  }

  handleSubmit(): void {
    if (this.price <= 0) {
      alert("Price must be greater than 0");
      return;
    }

    if (this.name.length < 3) {
      alert("Name must have at least 3 characters");
      return;
    }

    if (this.description.length < 10) {
      alert("Description must have at least 10 characters");
      return;
    }

    this.backendService.editProduct({
      id: this.productId,
      name: this.name,
      price: this.price,
      description: this.description,
      category: this.category
    });

    this.router.navigate(['/viewProducts', this.category]);
  }
}
