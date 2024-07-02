import { Routes } from '@angular/router';
import { HomePageComponent } from './home-page/home-page.component';
import { SelectCategoryPageComponent } from './select-category-page/select-category-page.component';
import { ViewProductsPageComponent } from './view-products-page/view-products-page.component';
import { EditProductPageComponent } from './edit-product-page/edit-product-page.component';
import { ViewCartPageComponent } from './view-cart-page/view-cart-page.component';
import { LoginPageComponent } from './login-page/login-page.component';

export const routes: Routes = [
    {path: 'home', component: HomePageComponent},
    {path:'selectCategory', component: SelectCategoryPageComponent},
    {path: 'viewProducts/:category', component: ViewProductsPageComponent},
    {path: 'editProduct/:id', component: EditProductPageComponent},
    {path: 'viewCart', component: ViewCartPageComponent},
    {path: 'login', component: LoginPageComponent},
    {path: '**', redirectTo: '/login', pathMatch: 'full'}
];
