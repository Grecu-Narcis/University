import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Product } from '../app/view-products-page/view-products-page.component';

@Injectable({
  providedIn: 'root'
})
export class BackendService {
  loginUser(username: string, password: string) {
    return this.http.post<any>('http://localhost:5189/api/login/login', {
      "username": username,
      "password": password
    }, {observe: 'response'});
  }

  constructor(private http: HttpClient) { }

  getCategories(): Observable<any[]> {
    return this.http.get<any[]>('http://localhost:5189/api/products/getCategories');
  }

  getAllProducts(category: string, currentPage: number): Observable<any[]> {
    return this.http.get<any[]>('http://localhost:5189/api/products/getAllProductsByCategory/' + category + "/" + currentPage);
  }

  getProductsInCart(): Observable<any[]> {
    return this.http.get<any[]>('http://localhost:5189/api/products/getProductsInCart');
  }

  addToCart(productID: number): void {
    this.http.post<any>('http://localhost:5189/api/products/addToCart', { productID: productID })
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
    return this.http.get<any>('http://localhost:5189/api/products/getProductsDetails/' + id);
  }

  editProduct(product: Product): void {
    this.http.put<any>('http://localhost:5189/api/products/updateProduct', product)
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
    return this.http.get<any[]>('http://localhost:5189/api/products/getCart');
  }

  removeFromCart(productId: number): void {
    this.http.delete<any>('http://localhost:5189/api/products/removeFromCart/' + productId).subscribe(
      () => {
        console.log('Product removed from cart');
      }
    );
  }
}
