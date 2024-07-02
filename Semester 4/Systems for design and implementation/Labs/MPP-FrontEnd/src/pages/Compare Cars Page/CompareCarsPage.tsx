import { useContext } from 'react';
import { Layout } from '../../shared/components/layout/Layout';

import './CompareCarsPage.css';
import { CompareCarsContext } from '../../contexts/CompareCarsContext';
import { Button } from '../../shared/components/button/Button';
import { useNavigate } from 'react-router-dom';

export default function CompareCarsPage() {
    const compareCarsContext = useContext(CompareCarsContext);
    const navigate = useNavigate();

    if (compareCarsContext == null) return;
    const cars = compareCarsContext.cars;

    return (
        <Layout>
            <div className='main-content'>
                <table className='cars-table'>
                    <thead>
                        <tr>
                            <td></td>
                            {cars.map((car, index) => (
                                <td key={index}>
                                    {car.getBrand()} {car.getModel()}
                                </td>
                            ))}
                        </tr>
                    </thead>
                    <tbody>
                        <tr>
                            <td>Year</td>
                            {cars.map((car, index) => (
                                <td key={index}>{car.getYear()}</td>
                            ))}
                        </tr>

                        <tr>
                            <td>Price</td>
                            {cars.map((car, index) => (
                                <td key={index}>{car.getPrice()}$</td>
                            ))}
                        </tr>

                        <tr>
                            <td>Mileage</td>
                            {cars.map((car, index) => (
                                <td key={index}>{car.getMileage()} km</td>
                            ))}
                        </tr>

                        <tr>
                            <td>Fuel type</td>
                            {cars.map((car, index) => (
                                <td key={index}>{car.getFuelType()}</td>
                            ))}
                        </tr>
                    </tbody>
                </table>

                <Button
                    type='button'
                    buttonMessage='Clear'
                    onClick={() => {
                        compareCarsContext.clearCars();
                        navigate('/home');
                    }}
                />
            </div>
        </Layout>
    );
}
