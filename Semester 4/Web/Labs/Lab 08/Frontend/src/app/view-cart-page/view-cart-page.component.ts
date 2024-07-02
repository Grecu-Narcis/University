import { Component } from '@angular/core';
import { BackendService } from '../../services/BackendService';
import { ActivatedRoute, Router } from '@angular/router';
import { Product } from '../view-products-page/view-products-page.component';

@Component({
  selector: 'app-view-cart-page',
  standalone: true,
  imports: [],
  templateUrl: './view-cart-page.component.html',
  styleUrl: './view-cart-page.component.css'
})
export class ViewCartPageComponent {
  public products: Product[] = [];
  public showModal: boolean = false;
  public productId: number = -1;

  constructor(private backendService: BackendService, private route: ActivatedRoute, private router: Router) { }

  ngOnInit(): void {
    this.backendService.getCart().subscribe((data: Product[]) => {
      this.products = data;
    });
  }

  handleRemoveFromCart(productId: number): void {
    this.productId = productId;
    this.showModal = true;
  }

  handleModalClose(): void {
    this.showModal = false;
  }

  handleModalConfirm(): void {
    this.showModal = false;
    this.products = this.products.filter(product => product.id !== this.productId);
    console.log('Removing product with id', this.productId);

    this.backendService.removeFromCart(this.productId);
  }
}
