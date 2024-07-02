import { Link } from 'react-router-dom';
import { Button } from '../../shared/components/button/Button';
import { Layout } from '../../shared/components/layout/Layout';

import './LandingPage.css';

export default function LandingPage() {
    return (
        <Layout>
            <div className='main-div-landing'>
                <div className='welcome-header' data-testid='welcome-header'>
                    <div className='welcome-message' data-testid='welcome-message'>
                        Shift into gear with our amazing car offers!
                    </div>
                    <Link to={'/viewDealers'}>
                        {' '}
                        <Button
                            type='button'
                            buttonMessage='Start buying now'
                            className='start-renting-button'
                            data-testid='start-renting-button'
                        />{' '}
                    </Link>
                </div>

                <div className='landing-info' data-testid='landing-info'>
                    <div className='landing-title'>Travel Wheels - Your Trusted Destination for Quality New and Pre-Owned Vehicles</div>
                    <div className='landing-description'>
                        Discover your perfect ride at Travel Wheels! Explore our wide selection of quality new and pre-owned vehicles,
                        tailored financing options, and exceptional customer service. Drive away with confidence and style. Your journey
                        begins at Travel Wheels.
                    </div>
                </div>
            </div>
        </Layout>
    );
}
