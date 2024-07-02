import { useRef } from 'react';
import { Button } from '../../shared/components/button/Button';
import { Layout } from '../../shared/components/layout/Layout';

import './AddCarPage.css';
import { FormEntry } from '../../features/CRUD Operations/User Form/Form Entry/FormEntry';
import { addCar } from '../../services/Cars Service/CarsService';
import { useNavigate } from 'react-router-dom';

function getCarData(
    brandInput: React.RefObject<HTMLInputElement>,
    modelInput: React.RefObject<HTMLInputElement>,
    mileageInput: React.RefObject<HTMLInputElement>,
    fuelTypeInput: React.RefObject<HTMLInputElement>,
    yearInput: React.RefObject<HTMLInputElement>,
    priceInput: React.RefObject<HTMLInputElement>,
) {
    const brand: string = brandInput.current!.value,
        model: string = modelInput.current!.value,
        mileage: number = parseInt(mileageInput.current!.value),
        fuelType: string = fuelTypeInput.current!.value,
        year: number = parseInt(yearInput.current!.value),
        price: number = parseInt(priceInput.current!.value);

    return { brand, model, mileage, fuelType, year, price };
}

export default function AddCarPage() {
    const brandInput = useRef<HTMLInputElement>(null);
    const modelInput = useRef<HTMLInputElement>(null);
    const mileageInput = useRef<HTMLInputElement>(null);
    const fuelTypeInput = useRef<HTMLInputElement>(null);
    const yearInput = useRef<HTMLInputElement>(null);
    const priceInput = useRef<HTMLInputElement>(null);

    const navigate = useNavigate();

    const handleAddCar = () => {
        const { brand, model, mileage, fuelType, year, price } = getCarData(
            brandInput,
            modelInput,
            mileageInput,
            fuelTypeInput,
            yearInput,
            priceInput,
        );

        addCar(brand, model, mileage, fuelType, year, price).then(() => {
            navigate('/cars/' + localStorage.getItem('userId'));
        });
    };

    return (
        <Layout>
            <form className='car-form'>
                <FormEntry label='Brand' placeHolder='Brand' ref={brandInput} />
                <FormEntry label='Model' placeHolder='Model' ref={modelInput} />
                <FormEntry label='Mileage' placeHolder='Mileage' ref={mileageInput} type='number' />
                <FormEntry label='Fuel type' placeHolder='Gasoline' ref={fuelTypeInput} />
                <FormEntry label='Year' placeHolder='2005' ref={yearInput} type='number' />
                <FormEntry label='Price' placeHolder='2999' ref={priceInput} type='number' />

                <Button type='button' buttonMessage='Add car' className='car-add-button' onClick={handleAddCar} />
            </form>
        </Layout>
    );
}
