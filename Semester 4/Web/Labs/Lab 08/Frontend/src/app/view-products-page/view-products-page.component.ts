import { Component } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { BackendService } from '../../services/BackendService';
import { RouterModule } from '@angular/router';

export type Product = {
  id: number;
  name: string;
  description: string;
  price: number;
  category: string;
}

@Component({
  selector: 'app-view-products-page',
  standalone: true,
  imports: [RouterModule],
  templateUrl: './view-products-page.component.html',
  styleUrl: './view-products-page.component.css'
})
export class ViewProductsPageComponent {
  public category: string = '';
  public products: Product[] = [];
  public currentPage: number = 1;
  public pageProducts: Product[] = [];
  public productsInCart: number[] = [];

  isNextDisabled: boolean = false;
  isPrevDisabled: boolean = true;

  constructor(private backendService: BackendService, private route: ActivatedRoute, private router: Router) { }

  ngOnInit(): void {
    this.category = this.route.snapshot.paramMap.get('category')!;
    this.backendService.getAllProducts(this.category, this.currentPage).subscribe((data: any) => {
      this.products = data.products;
      let totalCount = data.total;
      this.pageProducts = this.products;

      if (this.currentPage * 5 >= totalCount) {
        this.isNextDisabled = true;
      }

      if (this.currentPage == 1)
        this.isPrevDisabled = true;
    });

    this.backendService.getProductsInCart().subscribe((data: any[]) => {
      console.log("data");
      console.log(data);
      this.productsInCart = data.map(p => p.productID);
    });
  }

  isDisabled(product: Product): boolean {
    return this.productsInCart.some(p => p === product.id);
  }

  handleOnClickEdit(product: Product): void {
    this.router.navigate(['/editProduct', product.id]);
  }

  handleOnClickAdd(product: Product) {
    this.productsInCart.push(product.id);
    this.backendService.addToCart(product.id);
  }

  onClickPrev(): void {
    if (this.currentPage === 1) {
      return;
    }
    this.currentPage--;
    
    this.backendService.getAllProducts(this.category, this.currentPage).subscribe((data: any) => {
      this.products = data.products;
      this.pageProducts = this.products;

      if (this.currentPage == 1)
        this.isPrevDisabled = true;
    });

    if (this.currentPage === 1) {
      this.isPrevDisabled = true;
    }
    this.isNextDisabled = false;
  }

  onClickNext(): void {
    this.currentPage++;
    this.backendService.getAllProducts(this.category, this.currentPage).subscribe((data: any) => {
      this.products = data.products;
      let totalCount = data.total;
      this.pageProducts = this.products;

      if (this.currentPage * 5 >= totalCount) {
        this.isNextDisabled = true;
      }

      if (this.currentPage == 1)
        this.isPrevDisabled = true;
    });

    this.isPrevDisabled = false;
  }
}


