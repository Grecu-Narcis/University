import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Product } from '../app/view-products-page/view-products-page.component';

@Injectable({
  providedIn: 'root'
})
export class BackendService {

  constructor(private http: HttpClient) { }

  getCategories(): Observable<any[]> {
    return this.http.get<any[]>('http://localhost/Lab07/getCategories.php');
  }

  getAllProducts(category: string, currentPage: number): Observable<any[]> {
    return this.http.get<any[]>('http://localhost/Lab07/getAllProductsByCategory.php?category=' + category + "&page=" + currentPage);
  }

  getProductsInCart(): Observable<any[]> {
    return this.http.get<any[]>('http://localhost/Lab07/getProductsInCart.php');
  }

  addToCart(productID: number): void {
    this.http.post<any>('http://localhost/Lab07/addToCart.php', { productID: productID })
      .subscribe(
        response => {
          console.log('Product added to cart');
          console.log(response);
        },
        error => {
          console.error('Error', error);
        }
      );
  }

  getProductById(id: number): Observable<any> {
    return this.http.get<any>('http://localhost/Lab07/getProductDetails.php?id=' + id);
  }

  editProduct(product: Product): void {
    this.http.put<any>('http://localhost/Lab07/updateProduct.php', product)
      .subscribe(
        response => {
          console.log('Product edited');
          console.log(response);
        },
        error => {
          console.error('Error', error);
        }
      );
  }

  getCart(): Observable<any[]> {
    return this.http.get<any[]>('http://localhost/Lab07/getCart.php');
  }

  removeFromCart(productId: number): void {
    const headers = new HttpHeaders({ 'Content-Type': 'application/json' });
    const options = { headers, body: { id: productId } };
    this.http.delete<any>('http://localhost/Lab07/deleteFromCart.php', options).subscribe(
      () => {
        console.log('Product removed from cart');
      }
    );
  }
}
