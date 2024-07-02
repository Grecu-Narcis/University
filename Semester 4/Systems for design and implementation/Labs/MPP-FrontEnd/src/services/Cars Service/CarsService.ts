import axios from "axios";
import { CarDTO } from "../../types/CarDTO.types";
import { Car } from "../../models/car";
import { endPointUrl } from "../config";

const apiEndPoint = endPointUrl + '/api/cars';

export function convertDtoToCar(carToConvert: CarDTO) {
    return new Car(carToConvert.id, carToConvert.brand, carToConvert.model, carToConvert.year, 
        carToConvert.price, carToConvert.pictureUrl, carToConvert.mileage, carToConvert.fuelType);
}

export async function getCarById(carId: number) {
    try {
        const response = await axios.get(apiEndPoint + '/getCar/' + carId);
        return convertDtoToCar(response.data);
    }

    catch (error) {
        console.error((error as Error).message);
        throw error;
    }
}

export async function getAllCarsByOwnerId(ownerId: number) {
    try {
        const response = await axios.get(apiEndPoint + '/getAllByOwnerId/' + ownerId,
            {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
        );
        const result: Car[] = [];
        response.data.forEach((currentCar: CarDTO) => {
            result.push(convertDtoToCar(currentCar));
        });

        return result;
    }

    catch (error) {
        console.error((error as Error).message);
        return [];
    }
}

export async function getPageOfCarsByOwnerId(ownerId: number, pageNumber: number, pageSize: number) {
    try {
        const response = await axios.get(apiEndPoint + '/getPageByOwnerId' + 
        '?ownerId=' + ownerId + '&page=' + pageNumber + '&pageSize=' + pageSize);
        const result: Car[] = [];
        response.data.forEach((currentCar: CarDTO) => {
            result.push(convertDtoToCar(currentCar));
        });

        return result;
    }

    catch (error) {
        console.error((error as Error).message);
        return [];
    }
}

export async function getCarsCountByOwnerId(ownerId: number): Promise<number> {
    try {
        const response = await axios.get(apiEndPoint + '/getCarsCount/' + ownerId);
        return response.data;
    }

    catch (error) {
        console.error((error as Error).message);
        return 0;
    }
}

export async function getCarsPage(pageNumber: number, pageSize: number): Promise<Car[]> {
    try {
        const response = await axios.get(apiEndPoint + '/getPage?page=' + pageNumber + '&size=' + pageSize,
            {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
        );

        const result: Car[] = [];
        response.data.forEach((currentCar: CarDTO) => {
            result.push(convertDtoToCar(currentCar));
        });

        return result;
    }
    
    catch (error) {
        console.error((error as Error).message);

        return [];
    }
}

export async function getTotalCarCount(): Promise<number> {
    try {
        const response = await axios.get(apiEndPoint + '/getTotalCarCount',
            {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
        );
        return response.data;
    }

    catch (error) {
        console.error((error as Error).message);
        return 0;
    }
}

export async function getAllCars(): Promise<CarDTO[]> {
    try {
        const response = await axios.get<CarDTO[]>(apiEndPoint + '/getAll',
            {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
        );

        return response.data;
    }

    catch (error) {
        console.error((error as Error).message);

        return [];
    }
}

export async function addCar(brand: string, model: string, mileage: number, fuelType: string, year: number, price: number) {
    try {
        await axios.post(apiEndPoint + '/addCar', {
            brand: brand,
            model: model,
            mileage: mileage,
            fuelType: fuelType,
            year: year,
            price: price,
            ownerId: parseInt(localStorage.getItem('userId')!)
        },
            {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
        );
    }
    catch (error) {
        console.log(error);
    }
}

export async function updateCar(carToUpdate: Car) {
    try {
        await axios.put(apiEndPoint + '/updateCar', carToUpdate, 
            {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
        );
    }

    catch (error) {
        console.error((error as Error).message);
    }
}

export async function deleteCar(carId: string) {
    const response = await axios.delete(apiEndPoint + '/deleteCar/' + carId,
        {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
    );

    return response.data;
}