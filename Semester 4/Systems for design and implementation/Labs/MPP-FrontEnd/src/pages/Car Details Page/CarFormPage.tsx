import { useContext, useEffect, useRef, useState } from 'react';
import { useNavigate, useParams } from 'react-router-dom';
import { Car } from '../../models/car';
import { deleteCar, getCarById, updateCar } from '../../services/Cars Service/CarsService';
import LoadingPage from '../Loading Page/LoadingPage';
import { Layout } from '../../shared/components/layout/Layout';

import './CarFormPage.css';
import { Button } from '../../shared/components/button/Button';

import Chat from '../../features/Chat/AIChat';
import { CompareCarsContext } from '../../contexts/CompareCarsContext';
import ShareButton from '../../features/Share Button/ShareButton';
import NotificationCard from '../../features/Notification Card/NotificationCard';

function getCarData(
    brandInput: React.RefObject<HTMLInputElement>,
    modelInput: React.RefObject<HTMLInputElement>,
    mileageInput: React.RefObject<HTMLInputElement>,
    fuelTypeInput: React.RefObject<HTMLInputElement>,
    yearInput: React.RefObject<HTMLInputElement>,
    priceInput: React.RefObject<HTMLInputElement>,
    currentCar: Car,
) {
    const brand: string = brandInput.current!.value,
        model: string = modelInput.current!.value,
        mileage: number = parseInt(mileageInput.current!.value),
        fuelType: string = fuelTypeInput.current!.value,
        year: number = parseInt(yearInput.current!.value),
        price: number = parseInt(priceInput.current!.value);

    return new Car(currentCar.getId(), brand, model, year, price, currentCar.getPictureUrl(), mileage, fuelType);
}

/**
 * CarForm
 *
 * A form component for updating car details.
 *
 * This component fetches a specific car's details based on the `carId` parameter from the URL,
 * and provides a form to update the car's brand, model, mileage, fuel type, year, and price.
 * On submission, it updates the car details via an API call and navigates back to the home page.
 *
 * @returns JSX.Element
 * @example
 * <CarForm />
 */
export default function CarDetailsPage() {
    const { carId } = useParams();
    const navigate = useNavigate();

    const [givenCar, setGivenCar] = useState<Car>();
    const [isLoading, setIsLoading] = useState<boolean>(true);
    const [showNotification, setShowNotification] = useState<boolean>(false);

    const compareCarsContext = useContext(CompareCarsContext)!;

    const isDisabled = localStorage.getItem('userRole') === 'USER' || !localStorage.getItem('userRole');

    if (carId === undefined) {
        navigate('/');
        return;
    }

    const brandInput = useRef<HTMLInputElement>(null);
    const modelInput = useRef<HTMLInputElement>(null);
    const mileageInput = useRef<HTMLInputElement>(null);
    const fuelTypeInput = useRef<HTMLInputElement>(null);
    const yearInput = useRef<HTMLInputElement>(null);
    const priceInput = useRef<HTMLInputElement>(null);

    const handleError = () => {
        navigate('/home');
        return;
    };

    useEffect(() => {
        getCarById(parseInt(carId))
            .then((response) => {
                setGivenCar(response);
                setIsLoading(false);
                console.log(response);
            })
            .catch(handleError);
    }, []);

    const handleUpdateClick = () => {
        const updatedCar = getCarData(brandInput, modelInput, mileageInput, fuelTypeInput, yearInput, priceInput, givenCar!);
        console.log(updatedCar);
        updateCar(updatedCar)
            .then(() => navigate('/cars/' + localStorage.getItem('userId')))
            .catch(handleError);
    };

    const handleRemoveClick = () => {
        deleteCar(carId)
            .then(() => navigate('/cars/' + localStorage.getItem('userId')))
            .catch(handleError);
    };

    if (isLoading) return <LoadingPage />;

    return (
        <Layout>
            <img src={'/assets/cars/' + givenCar?.getPictureUrl()} className='car-detail-image' alt='car' />
            <form className='car-form'>
                <label htmlFor='brand' className='form-label'>
                    Brand:
                </label>
                <input
                    type='text'
                    className='form-input'
                    id='brand'
                    name='brand'
                    defaultValue={givenCar?.getBrand()}
                    ref={brandInput}
                    disabled={isDisabled}
                />

                <label htmlFor='model' className='form-label'>
                    Model:
                </label>
                <input
                    type='text'
                    className='form-input'
                    id='model'
                    name='model'
                    defaultValue={givenCar?.getModel()}
                    ref={modelInput}
                    disabled={isDisabled}
                />

                <label htmlFor='mileage' className='form-label'>
                    Mileage:
                </label>
                <input
                    type='text'
                    className='form-input'
                    id='mileage'
                    name='mileage'
                    defaultValue={givenCar?.getMileage().toString()}
                    ref={mileageInput}
                    disabled={isDisabled}
                />

                <label htmlFor='fuelType' className='form-label'>
                    Fuel Type:
                </label>
                <input
                    type='text'
                    className='form-input'
                    id='fuelType'
                    name='fuelType'
                    defaultValue={givenCar?.getFuelType()}
                    ref={fuelTypeInput}
                    disabled={isDisabled}
                />

                <label htmlFor='year' className='form-label'>
                    Year:
                </label>
                <input
                    type='text'
                    className='form-input'
                    id='year'
                    name='year'
                    defaultValue={givenCar?.getYear().toString()}
                    ref={yearInput}
                    disabled={isDisabled}
                />

                <label htmlFor='price' className='form-label'>
                    Price:
                </label>
                <input
                    type='text'
                    className='form-input'
                    id='price'
                    name='price'
                    defaultValue={givenCar?.getPrice().toString()}
                    ref={priceInput}
                    disabled={isDisabled}
                />

                <div className='car-details-options'>
                    {!isDisabled && (
                        <>
                            <Button type='button' buttonMessage='Update' onClick={handleUpdateClick} className='car-update-button' />
                            <Button type='button' buttonMessage='Remove' onClick={handleRemoveClick} className='car-delete-button' />
                        </>
                    )}

                    {isDisabled && (
                        <div className='user-options'>
                            <Button
                                type='button'
                                buttonMessage='Add to compare'
                                className='add-button'
                                onClick={() => {
                                    compareCarsContext.addCar(givenCar!);
                                    setShowNotification(true);
                                    const timeout = setTimeout(() => {
                                        setShowNotification(false);
                                    }, 4000);

                                    return () => clearInterval(timeout);
                                }}
                            />
                        </div>
                    )}
                    <ShareButton car={givenCar!} />
                </div>
            </form>

            <Chat carId={carId} />
            {showNotification && <NotificationCard color='green'>Car added to compare list</NotificationCard>}
        </Layout>
    );
}
