import './CompareCarsPopup.css';
import { useContext, useState } from 'react';
import { CompareCarsContext } from '../../../contexts/CompareCarsContext';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faArrowRightArrowLeft } from '@fortawesome/free-solid-svg-icons';
import { useNavigate } from 'react-router-dom';

export default function CompareCarsPopup() {
    const compareCarsContext = useContext(CompareCarsContext);
    const [displayList, setDisplayList] = useState<boolean>(false);
    const navigate = useNavigate();

    if (compareCarsContext == null) return;

    return (
        <div className='compare-popup'>
            {displayList && (
                <div className='compare-cars-list'>
                    {compareCarsContext.cars.map((car, index) => (
                        <div className='car-item' key={index}>
                            {car.getBrand()} {car.getModel()}
                        </div>
                    ))}
                </div>
            )}
            <div className='compare-icon-area' onMouseEnter={() => setDisplayList(true)} onMouseLeave={() => setDisplayList(false)}>
                <FontAwesomeIcon icon={faArrowRightArrowLeft} className='compare-icon' onClick={() => navigate('/compare')} />
            </div>
        </div>
    );
}
