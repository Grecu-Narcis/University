#include "TutorialValidator.h"
#include "ValidatorException.h"

void TutorialValidator::validate(const Tutorial& tutorialToValidate)
{
	string errorMessage = "";

	if (tutorialToValidate.getPresenter().size() < 3)
		errorMessage += "Presenter name must be at least 3 characters long.\n";

	if (tutorialToValidate.getTitle().size() < 3)
		errorMessage += "Title must be at least 3 characters long.\n";

	if (tutorialToValidate.getLink().size() < 3)
		errorMessage += "Link must be at least 3 characters long.\n";

	if (tutorialToValidate.getNumberOfLikes() < 0)
		errorMessage += "Number of likes can't be negative.\n";

	if (tutorialToValidate.getDuration().minutes < 0)
		errorMessage += "Minutes can't be negative.\n";

	if (tutorialToValidate.getDuration().seconds < 0)
		errorMessage += "Seconds can't be negative.\n";

	if (errorMessage != "")
		throw ValidatorException(errorMessage);
}
