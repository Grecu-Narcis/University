import { useNavigate } from 'react-router-dom';
import { CarCardProps } from '../../types/CarCardProps.types';

import './CarCard.css';

/**
 * CarCard Component
 *
 * A component representing a card view for displaying car details.
 *
 * This component renders a card view with details of a given car object, including
 * the car image, brand, model, mileage, fuel type, year, and price. It also provides
 * a button to view more details of the car.
 *
 * @component
 * @param {Object} props - The props object containing the givenCar data.
 * @param {Car} props.givenCar - The car object containing details to be displayed.
 * @returns {JSX.Element} - Rendered CarCard component.
 * @example
 * <CarCard givenCar={carData} />
 */
export function CarCard({ givenCar }: CarCardProps) {
    const imagePath: string = '/assets/cars/' + givenCar.getPictureUrl();

    const navigate = useNavigate();

    const handleViewCar = () => {
        navigate('/viewCar/' + givenCar.getId());
    };

    return (
        <div className='car-card'>
            <div className='car-image-details'>
                <img src={imagePath} className='car-image' alt='car' />
                <div className='car-info'>
                    <div className='make-mileage'>
                        <div className='make-brand'>{givenCar.getBrand() + ' ' + givenCar.getModel()}</div>
                        <div className='car-details'>
                            <div className='mileage-fuel'>{givenCar.getMileage().toLocaleString() + ' km, ' + givenCar.getFuelType()}</div>
                            <div className='make-year'>{givenCar.getYear()}</div>
                        </div>
                    </div>
                </div>

                <div className='price-view'>
                    <div className='price'>{givenCar.getPrice().toLocaleString() + ' €'}</div>
                    {/* {!readOnly && ( */}
                    <button type='button' className='view-button' onClick={handleViewCar}>
                        View
                    </button>
                    {/* )} */}
                </div>
            </div>
        </div>
    );
}
