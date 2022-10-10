/*
	Purpose:	https://go.dev/tour/methods/25

	TODO:	save the image on disk
*/
package main

import (
	"image"
	"image/color"
	//"math"
	"golang.org/x/tour/pic"
)

type Image struct {
	width, height uint
	prev, next    int
}

func (img Image) ColorModel() color.Model {
	return color.RGBAModel
}

func (img Image) Bounds() image.Rectangle {
	return image.Rect(0, 0, int(img.width), int(img.height))
}

func (img Image) At1(x, y int) color.Color {
	v := uint8((x + y) / 2)
	return color.RGBA{v, v, 255, 255}
}

func (img Image) At2(x, y int) color.Color {
	v := uint8(x ^ y)
	return color.RGBA{v, v, 255, 255}
}

func (img Image) At3(x, y int) color.Color {
	v := uint8(x * y)
	return color.RGBA{v, v, 255, 255}
}

// TODO: create a beautiful image
func (img *Image) At4(x, y int) color.Color {
	img.prev, img.next = img.next, img.prev+img.next
	v := uint8(img.next)
	return color.RGBA{v, v, 255, 255}
}

func (img *Image) At(x, y int) color.Color {
	return img.At2(x, y)
}

func main() {
	m := Image{256, 256, -1, 1}
	pic.ShowImage(&m)
}
