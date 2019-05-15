#pragma once

#include "DicomImage.g.h"

namespace winrt::GridArtifacts::implementation
{
	using namespace winrt::Windows::Storage;

	struct DicomImage : DicomImageT<DicomImage>
    {
        DicomImage() = default;

		DicomImage(winrt::Windows::Storage::FileProperties::ImageProperties const& props,
			winrt::Windows::Storage::StorageFile const& imageFile,
			hstring const& name,
			hstring const& type) :
			m_imageProperties(props),
			m_imageName(name),
			m_imageFileType(type),
			m_imageFile(imageFile)
		{
		}

		// File and information properties.
		Windows::Storage::StorageFile ImageFile() const
		{
			return m_imageFile;
		}

		Windows::Storage::FileProperties::ImageProperties ImageProperties() const
		{
			return m_imageProperties;
		}

		hstring ImageName() const
		{
			return m_imageName;
		}

		hstring ImageFileType() const
		{
			return m_imageFileType;
		}

		// Gets or sets the image title.
		hstring ImageTitle() const
		{
			return m_imageProperties.Title() == L"" ? m_imageName : m_imageProperties.Title();
		}

	private:
		// File and information fields.
		FileProperties::ImageProperties m_imageProperties{ nullptr };
		StorageFile m_imageFile{ nullptr };
		hstring m_imageName;
		hstring m_imageFileType;
		hstring m_imageTitle;
	};
}

namespace winrt::GridArtifacts::factory_implementation
{
    struct DicomImage : DicomImageT<DicomImage, implementation::DicomImage>
    {
    };
}
